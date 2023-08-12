#ifndef INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP
#define INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP

#include <utility>
#include <algorithm>
#include <exception>

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "vector.hpp"

namespace yLab::geometry
{

namespace detail
{

enum class Axes { x, y, z };

template<typename T>
Axes deduce_coordinate_to_set_zero (const Vector<T> &norm)
{
    auto x = std::abs (norm.x_);
    auto y = std::abs (norm.y_);
    auto z = std::abs (norm.z_);

    if (cmp::greater (x, y) && cmp::greater (x, z))
        return Axes::x;
    else if (y > z)
        return Axes::y;
    else
        return Axes::z;
}

template<typename T>
Point_2D<T> project_point (const Point_3D<T> &pt, Axes coordinate_to_set_zero)
{
    switch (coordinate_to_set_zero)
    {
        case Axes::x:
            return Point_2D{pt.y(), pt.z()};

        case Axes::y:
            return Point_2D{pt.z(), pt.x()};

        case Axes::z:
            return Point_2D{pt.x(), pt.y()};

        default:
            throw std::runtime_error ("Unexpected value of coordinate_to_set_zero");
    }
}

template<typename T>
Segment<Point_2D<T>> project_segment (const Segment<Point_3D<T>> &seg,
                                      Axes coordinate_to_set_zero)
{
    switch (coordinate_to_set_zero)
    {
        case Axes::x:
        {
            return Segment{Point_2D{seg.P().y(), seg.P().z()},
                           Point_2D{seg.Q().y(), seg.Q().z()}};
        }

        case Axes::y:
        {
            return Segment{Point_2D{seg.P().z(), seg.P().x()},
                           Point_2D{seg.Q().z(), seg.Q().x()}};
        }

        case Axes::z:
        {
            return Segment{Point_2D{seg.P().x(), seg.P().y()},
                           Point_2D{seg.Q().x(), seg.Q().y()}};
        }

        default:
            throw std::runtime_error ("Unexpected value of coordinate_to_set_zero");
    }
}

template<typename T>
Triangle<Point_2D<T>> project_triangle (const Triangle<Point_3D<T>> &tr,
                                        Axes coordinate_to_set_zero)
{
    switch (coordinate_to_set_zero)
    {
        case Axes::x:
        {
            return Triangle{Point_2D{tr.P().y(), tr.P().z()},
                            Point_2D{tr.Q().y(), tr.Q().z()},
                            Point_2D{tr.R().y(), tr.R().z()}};
        }

        case Axes::y:
        {
            return Triangle{Point_2D{tr.P().z(), tr.P().x()},
                            Point_2D{tr.Q().z(), tr.Q().x()},
                            Point_2D{tr.R().z(), tr.R().x()}};
        }

        case Axes::z:
        {
            return Triangle{Point_2D{tr.P().x(), tr.P().y()},
                            Point_2D{tr.Q().x(), tr.Q().y()},
                            Point_2D{tr.R().x(), tr.R().y()}};
        }

        default:
            throw std::runtime_error ("Unexpected value of coordinate_to_set_zero");
    }
}

template<typename T>
auto space_transformation (const Point_3D<T> &pt, const Triangle<Point_3D<T>> &tr)
{
    using point_2d = Point_2D<T>;
    using triangle_2d = Triangle<point_2d>;
    using point_triangle_pair = std::pair<point_2d, triangle_2d>;

    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (tr.norm());

    return point_triangle_pair{project_point (pt, coordinate_to_set_zero),
                               project_triangle (tr, coordinate_to_set_zero)};
}

template<typename T>
auto space_transformation (const Triangle<Point_3D<T>> &tr, const Point_3D<T> &pt)
{
    return space_transformation (pt, tr);
}

template<typename T>
auto space_transformation (const Segment<Point_3D<T>> &seg_1, const Segment<Point_3D<T>> &seg_2)
{
    using segment_2d = Segment<Point_2D<T>>;
    using segment_pair = std::pair<segment_2d, segment_2d>;

    auto norm = vector_product (Vector{seg_1.P(), seg_1.Q()}, Vector{seg_2.P(), seg_2.Q()});
    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (norm);

    return segment_pair{project_segment (seg_1, coordinate_to_set_zero),
                        project_segment (seg_2, coordinate_to_set_zero)};
}

template<typename T>
auto space_transformation (const Segment<Point_3D<T>> &seg, const Triangle<Point_3D<T>> &tr)
{
    using segment_2d = Segment<Point_2D<T>>;
    using triangle_2d = Triangle<Point_2D<T>>;
    using segment_triangle_pair = std::pair<segment_2d, triangle_2d>;

    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (tr.norm());

    return segment_triangle_pair{project_segment (seg, coordinate_to_set_zero),
                                 project_triangle (tr, coordinate_to_set_zero)};
}

template<typename T>
auto space_transformation (const Triangle<Point_3D<T>> &tr, const Segment<Point_3D<T>> &seg)
{
    return space_transformation (seg, tr);
}

template<typename T>
auto space_transformation (const Triangle<Point_3D<T>> &tr_1, const Triangle<Point_3D<T>> &tr_2)
{
    using triangle_2d = Triangle<Point_2D<T>>;
    using triangle_pair = std::pair<triangle_2d, triangle_2d>;

    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (tr_1.norm());

    return triangle_pair{project_triangle (tr_1, coordinate_to_set_zero),
                         project_triangle (tr_2, coordinate_to_set_zero)};
}

} // namespace detail

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP
