// clang++ -std=c++20 -I../../include -I../../include/space_partitioning -I../../include/primitives/ -I../../include/intersection driver.cpp

#include <iostream>
#include <iterator>
#include <variant>
#include <vector>

#include "intersector.hpp"

using vector = yLab::geometry::Vector<float>;

using point_type    = yLab::geometry::Primitive_Traits<float>::point_type;
using segment_type  = yLab::geometry::Primitive_Traits<float>::segment_type;
using triangle_type = yLab::geometry::Primitive_Traits<float>::triangle_type;
using shape = yLab::geometry::Shape<float>;

using intersector = yLab::geometry::Intersector<float>;

namespace
{

std::vector<point_type> construct_points ()
{
    auto cin_iter = std::istream_iterator<int>{std::cin};
    auto cin_end  = std::istream_iterator<int>{};
    auto n_points = *cin_iter;
    cin_iter++;
    
    std::vector<point_type> points;
    for (auto i = 0; i != n_points && cin_iter != cin_end; ++i)
    {
        float x = *cin_iter++;
        float y = *cin_iter++;
        float z = *cin_iter++;
        
        points.push_back (point_type{x, y, z});
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
std::vector<shape> construct_shapes (it first, it last)
{
    std::vector<shape> triangles;
    triangles.reserve (std::distance (first, last) / 3);

    while (first != last)
    {
        auto &P = *first++;
        auto &Q = *first++;
        auto &R = *first++;
        
        try
        {
            triangle_type tr{P, Q, R};
            triangles.emplace_back (tr);
        }
        catch (yLab::geometry::Triangle_Is_Segment &expt)
        {
            segment_type seg = assemble_segment (P, Q, R);
            triangles.emplace_back (seg);
        }
        catch (yLab::geometry::Triangle_Is_Point &expt)
        {
            triangles.emplace_back (P);
        }
    }

    return triangles;
}

} // unnamed namespace

#define OCTREE_RULES

int main ()
{
    std::vector<point_type> points = construct_points ();
    std::vector<shape> shapes = construct_shapes (points.begin(), points.end());

    intersector collider {shapes.begin(), shapes.end()};
    collider.intersect_all();

    return 0;
}
