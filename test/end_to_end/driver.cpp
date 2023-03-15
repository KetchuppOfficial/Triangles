// clang++ -std=c++20 -I../../include -I../../include/space_partitioning -I../../include/primitives/ -I../../include/intersection driver.cpp

#include <iostream>
#include <iterator>
#include <variant>
#include <vector>

#include "intersector.hpp"

using distance_type = float;

using vector = yLab::geometry::Vector<distance_type>;

using point_type    = yLab::geometry::Primitive_Traits<distance_type>::point_type;
using segment_type  = yLab::geometry::Primitive_Traits<distance_type>::segment_type;
using triangle_type = yLab::geometry::Primitive_Traits<distance_type>::triangle_type;
using shape_type    = yLab::geometry::Indexed_Shape<distance_type>;

using intersector = yLab::geometry::Intersector<distance_type>;

namespace
{

std::vector<point_type> construct_points ()
{
    auto cin_iter = std::istream_iterator<float>{std::cin};
    auto cin_end  = std::istream_iterator<float>{};
    auto n_points = static_cast<std::size_t>(*cin_iter) * 3;
    cin_iter++;
    
    std::vector<point_type> points;
    points.reserve (n_points);

    for (auto i = 0; i != n_points && cin_iter != cin_end; ++i)
    {
        auto x = *cin_iter++;
        auto y = *cin_iter++;
        auto z = *cin_iter++;
        
        points.emplace_back (x, y, z);
    }

    return points;
}

segment_type assemble_segment (const point_type &P, const point_type &Q, const point_type &R)
{
    vector PR{P, R};
    vector QR{Q, R};

    if (are_oppositely_directed (PR, QR))
        return segment_type{P, Q};
    else if (PR.norm() > QR.norm())
        return segment_type{P, R};   
    else
        return segment_type{Q, R};
}

template<std::input_iterator it>
std::vector<shape_type> construct_shapes (it first, it last)
{
    std::vector<shape_type> triangles;
    triangles.reserve (std::distance (first, last) / 3);

    auto shape_i = 0;
    while (first != last)
    {
        auto &P = *first++;
        auto &Q = *first++;
        auto &R = *first++;
        
        try
        {
            triangle_type tr{P, Q, R};
            triangles.emplace_back (tr, shape_i);
        }
        catch (yLab::geometry::Triangle_Is_Segment &expt)
        {
            segment_type seg = assemble_segment (P, Q, R);
            triangles.emplace_back (seg, shape_i);
        }
        catch (yLab::geometry::Triangle_Is_Point &expt)
        {
            triangles.emplace_back (P, shape_i);
        }

        shape_i++;
    }

    return triangles;
}

} // unnamed namespace

#define OCTREE_RULES

int main ()
{
    std::vector<point_type> points = construct_points ();
    std::vector<shape_type> shapes = construct_shapes (points.begin(), points.end());

    intersector collider {shapes.begin(), shapes.end()};
    collider.intersect_all();
    collider.show_intersecting();

    return 0;
}
