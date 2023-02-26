#ifndef INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP
#define INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP

#include <utility>
#include <algorithm>
#include <cassert>
#include <exception>

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "vector.hpp"

namespace yLab::geometry
{

namespace detail
{

enum class Axises { x, y, z };

template<typename T>
Axises deduce_coordinate_to_set_zero (const Vector<T> &vec_1, const Vector<T> &vec_2)
{
    assert (are_collinear (vec_1, vec_2) == false);
    
    Vector norm = vector_product(vec_1, vec_2);
    auto x = std::abs (norm.x_);
    auto y = std::abs (norm.y_);
    auto z = std::abs (norm.z_);

    if (x > y && x > z)
        return Axises::x;
    else if (y > z)
        return Axises::y;
    else
        return Axises::z;
}

template<typename T>
Point_2D<T> project_point (const Point_3D<T> &pt, Axises coordinate_to_set_zero)
{
    switch (coordinate_to_set_zero)
    {
        case Axises::x:
            return Point_2D{pt.y_, pt.z_};

        case Axises::y:
            return Point_2D{pt.z_, pt.x_};

        case Axises::z:
            return Point_2D{pt.x_, pt.y_};

        default:
            throw std::runtime_error ("Unexpected value of coordinate_to_set_zero");
    }
}

template<typename T>
Segment<Point_2D<T>> project_segment (const Segment<Point_3D<T>> &seg,
                                      Axises coordinate_to_set_zero)
{
    switch (coordinate_to_set_zero)
    {
        case Axises::x:
        {
            return Segment{Point_2D{seg.P().y_, seg.P().z_}, 
                           Point_2D{seg.Q().y_, seg.Q().z_}};
        }

        case Axises::y:
        {
            return Segment{Point_2D{seg.P().z_, seg.P().x_}, 
                           Point_2D{seg.Q().z_, seg.Q().x_}};
        }

        case Axises::z:
        {
            return Segment{Point_2D{seg.P().x_, seg.P().y_}, 
                           Point_2D{seg.Q().x_, seg.Q().y_}};
        }

        default:
            throw std::runtime_error ("Unexpected value of coordinate_to_set_zero");
    }
}

template<typename T>
Triangle<Point_2D<T>> project_triangle (const Triangle<Point_3D<T>> &tr,
                                        Axises coordinate_to_set_zero)
{
    switch (coordinate_to_set_zero)
    {
        case Axises::x:
        {
            return Triangle{Point_2D{tr.P().y_, tr.P().z_}, 
                            Point_2D{tr.Q().y_, tr.Q().z_},
                            Point_2D{tr.R().y_, tr.R().z_}};
        }

        case Axises::y:
        {
            return Triangle{Point_2D{tr.P().z_, tr.P().x_}, 
                            Point_2D{tr.Q().z_, tr.Q().x_},
                            Point_2D{tr.R().z_, tr.R().x_}};
        }

        case Axises::z:
        {
            return Triangle{Point_2D{tr.P().x_, tr.P().y_}, 
                            Point_2D{tr.Q().x_, tr.Q().y_},
                            Point_2D{tr.R().x_, tr.R().y_}};
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
    
    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (Vector{tr.P(), tr.Q()},
                                                                 Vector{tr.P(), tr.R()});

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

    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (Vector{seg_1.P(), seg_1.Q()},
                                                                 Vector{seg_2.P(), seg_2.Q()});

    return segment_pair{project_segment (seg_1, coordinate_to_set_zero),
                        project_segment (seg_2, coordinate_to_set_zero)};
}

template<typename T>
auto space_transformation (const Segment<Point_3D<T>> &seg, const Triangle<Point_3D<T>> &tr)
{
    using segment_2d = Segment<Point_2D<T>>;
    using triangle_2d = Triangle<Point_2D<T>>;
    using segment_triangle_pair = std::pair<segment_2d, triangle_2d>;

    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (Vector{tr.P(), tr.Q()},
                                                                 Vector{tr.P(), tr.R()});

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

    auto coordinate_to_set_zero = deduce_coordinate_to_set_zero (Vector{tr_1.P(), tr_1.Q()},
                                                                 Vector{tr_1.P(), tr_1.R()});

    return triangle_pair{project_triangle (tr_1, coordinate_to_set_zero),
                         project_triangle (tr_2, coordinate_to_set_zero)};
}

} // namespace detail

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP
