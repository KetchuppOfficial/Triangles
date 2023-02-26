#include <iostream>
#include <iterator>
#include <variant>
#include <vector>

#include "point_point.hpp"
#include "point_segment.hpp"
#include "point_triangle.hpp"
#include "segment_segment.hpp"
#include "segment_triangle.hpp"
#include "triangle_triangle.hpp"

using point = yLab::geometry::Point_3D<float>;
using vector = yLab::geometry::Vector<float>;
using segment = yLab::geometry::Segment<point>;
using triangle = yLab::geometry::Triangle<point>;
using shape = std::variant<point, segment, triangle>;

namespace
{

std::vector<point> construct_points ()
{
    auto cin_iter = std::istream_iterator<int>{std::cin};
    auto cin_end  = std::istream_iterator<int>{};
    auto n_points = *cin_iter * 3;
    cin_iter++;
    
    std::vector<point> points;
    for (auto i = 0; i != n_points && cin_iter != cin_end; ++i)
    {
        float x = *cin_iter++;
        float y = *cin_iter++;
        float z = *cin_iter++;
        
        points.push_back (point{x, y, z});
    }

    return points;
}

segment assemble_segment (const point &P, const point &Q, const point &R)
{
    vector PR{P, R};
    vector QR{Q, R};

    if (are_oppositely_directed (PR, QR))
        return segment{P, Q};
    else if (PR.norm() > QR.norm())
        return segment{P, R};
    else
        return segment{Q, R};
}

std::vector<shape> construct_triangles (const std::vector<point> &points)
{
    auto n_triangles = points.size() / 3;
    std::vector<shape> triangles;

    for (auto i = 0; i != n_triangles;)
    {
        auto P = points[i++];
        auto Q = points[i++];
        auto R = points[i++];
        
        try
        {
            shape figure{triangle{P, Q, R}};
            triangles.push_back (std::get<triangle>(figure));
        }
        catch (yLab::geometry::Triangle_Is_Point &expt)
        {
            shape figure{P};
            triangles.push_back (std::get<point>(figure));
        }
        catch (yLab::geometry::Triangle_Is_Segment &expt)
        {
            shape figure = assemble_segment (P, Q, R);
            triangles.push_back (std::get<segment>(figure));
        }
    }

    return triangles;
}

void intersect_extremely_slow (const std::vector<shape> &triangles)
{
    auto n_triangles = triangles.size();
    for (auto i = 0; i != n_triangles; ++i)
    {
        for (auto j = i + 1; j != n_triangles; ++j)
        {
            auto intersection = std::visit ([](auto &shape_1, auto &shape_2)
                                            {
                                                return are_intersecting (shape_1, shape_2);
                                            },
                                            triangles[i], triangles[j]);

            if (intersection)
                std::cout << i << " " << j << std::endl;
        }
    }
}

} // unnamed namespace

int main ()
{
    std::vector<point> points    = construct_points ();
    std::vector<shape> triangles = construct_triangles (points);

    intersect_extremely_slow (triangles);

    return 0;
}
