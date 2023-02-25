#ifndef INCLUDE_INTERSECTION_HPP
#define INCLUDE_INTERSECTION_HPP

#include <exception>

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "vector.hpp"

#include "point_segment.hpp"
#include "point_triangle.hpp"
#include "segment_segment.hpp"
#include "segment_triangle.hpp"
#include "triangle_triangle.hpp"

namespace yLab::geometry
{

namespace detail
{

enum class Intersection
{
    point_point,
    point_segment,
    point_triangle,
    segment_segment,
    segment_triangle,
    triangle_triangle
};

inline constexpr auto deduce_intersection_type (Tr_Species tr_1, Tr_Species tr_2)
{
    auto sum = static_cast<int>(tr_1) + static_cast<int>(tr_2);

    switch (sum)
    {
        case -2:
            return Intersection::point_point;

        case -1:
            return Intersection::point_segment;

        case 0:
        {
            auto mult = static_cast<int>(tr_2) * static_cast<int>(tr_2);
            return (mult == 0) ? Intersection::segment_segment
                               : Intersection::point_triangle;
        }

        case 1:
            return Intersection::segment_triangle;

        case 2:
            return Intersection::triangle_triangle;

        default:
            throw std::runtime_error ("Something bad happened");
    }
}

template<typename T>
Segment<Point_3D<T>> triangle_to_segment (const Triangle<Point_3D<T>> &tr)
{
    Vector PR{tr.P(), tr.R()};
    Vector QR{tr.Q(), tr.R()};

    if (are_oppositely_directed (PR, QR))
        return Segment<Point_3D<T>>{tr.P(), tr.Q()};
    else if (PR.norm() > QR.norm())
        return Segment<Point_3D<T>>{tr.P(), tr.R()};
    else
        return Segment<Point_3D<T>>{tr.Q(), tr.R()};
}

} // namespace detail

template<typename T>
bool are_intersecting (const Triangle<Point_3D<T>> &tr_1, const Triangle<Point_3D<T>> &tr_2)
{
    switch (detail::deduce_intersection_type (tr_1.type(), tr_2.type()))
    {
        case detail::Intersection::point_point:
            return tr_1.P() == tr_2.P();

        case detail::Intersection::point_segment:
        {
            if (tr_1.type() == Tr_Species::segment)
                return detail::are_intersecting (detail::triangle_to_segment (tr_1), tr_2.P());
            else
                return detail::are_intersecting (detail::triangle_to_segment (tr_2), tr_1.P());
        }

        case detail::Intersection::point_triangle:
        {
            if (tr_1.type() == Tr_Species::triangle)
                return detail::are_intersecting (tr_1, tr_2.P());
            else
                return detail::are_intersecting (tr_2, tr_1.P());
        }

        case detail::Intersection::segment_segment:
        {   
            auto seg_1 = detail::triangle_to_segment (tr_1);
            auto seg_2 = detail::triangle_to_segment (tr_2);

            return detail::are_intersecting (seg_1, seg_2);
        }

        case detail::Intersection::segment_triangle:
        {
            if (tr_1.type() == Tr_Species::segment)
                return detail::are_intersecting (detail::triangle_to_segment (tr_1), tr_2);
            else
                return detail::are_intersecting (detail::triangle_to_segment (tr_2), tr_1);
        }

        case detail::Intersection::triangle_triangle:
            return detail::are_intersecting(tr_1, tr_2);

        default:
            throw std::runtime_error ("Not implemented yet");
    }
}

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_HPP
