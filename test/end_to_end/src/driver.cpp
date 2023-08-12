#include <iostream>
#include <iterator>
#include <variant>
#include <vector>
#include <chrono>
#include <fstream>

#include "collision_manager.hpp"

using distance_type = float;

using vector = yLab::geometry::Vector<distance_type>;

using point_type    = yLab::geometry::Primitive_Traits<distance_type>::point_type;
using segment_type  = yLab::geometry::Primitive_Traits<distance_type>::segment_type;
using triangle_type = yLab::geometry::Primitive_Traits<distance_type>::triangle_type;
using shape_type    = yLab::geometry::Indexed_Shape<distance_type>;

using collision_manager = yLab::geometry::Collision_Manager<distance_type>;

namespace
{

std::vector<point_type> construct_points ()
{
    auto cin_iter = std::istream_iterator<float>{std::cin};
    auto cin_end  = std::istream_iterator<float>{};
    auto n_points = static_cast<std::size_t>(*cin_iter) * 3;
    ++cin_iter;

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

int main ()
{
    using std::chrono::milliseconds;

    std::ofstream time_info{"time.info"};

    auto primitives_start = std::chrono::high_resolution_clock::now();
    std::vector<point_type> points = construct_points ();
    std::vector<shape_type> shapes = construct_shapes (points.begin(), points.end());
    auto primitives_finish = std::chrono::high_resolution_clock::now();

    collision_manager collider {shapes.begin(), shapes.end()};
    auto manager_finish = std::chrono::high_resolution_clock::now();

    collider.intersect_all();
    auto intersection_finish = std::chrono::high_resolution_clock::now();

    collider.show_intersecting();
    auto output_finish = std::chrono::high_resolution_clock::now();

    time_info << "Building of primitives            "
              << duration_cast<milliseconds>(primitives_finish - primitives_start).count()
              << " ms" << std::endl
              << "Construction of collision manager "
              << duration_cast<milliseconds>(manager_finish - primitives_finish).count()
              << " ms" << std::endl
              << "Intersection                      "
              << duration_cast<milliseconds>(intersection_finish - manager_finish).count()
              << " ms" << std::endl
              << "Output                            "
              << duration_cast<milliseconds>(output_finish - intersection_finish).count()
              << " ms" << std::endl;

    return 0;
}
