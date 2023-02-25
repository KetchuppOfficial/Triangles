#ifndef INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP
#define INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP

#include <utility>
#include <tuple>

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "vector.hpp"

namespace yLab::geometry
{

namespace detail
{

template<typename T>
Point_2D<T> point_transformation (const Point_3D<T> &point, const Point_3D<T> &origin, 
                                  const Vector<T> &x_axis,  const Vector<T> &y_axis)
{
    auto diff_x = point.x_ - origin.x_;
    auto diff_y = point.y_ - origin.y_;
    auto diff_z = point.z_ - origin.z_;

    Point_2D<T> pt{x_axis.x_ * diff_x + x_axis.y_ * diff_y + x_axis.z_ * diff_z,
                   y_axis.x_ * diff_x + y_axis.y_ * diff_y + y_axis.z_ * diff_z};

    return pt;
}

template<typename T>
auto get_2d_coordinates (const Triangle<Point_3D<T>> &tr)
{    
    Vector x_axis{tr.P(), tr.Q()};
    Vector z_axis = vector_product (x_axis, Vector{tr.P(), tr.R()});
    Vector y_axis = vector_product (z_axis, x_axis);

    x_axis.normalize();
    y_axis.normalize();

    return std::tuple<Point_3D<T>, Vector<T>, Vector<T>>{tr.P(), x_axis, y_axis};
}

template<typename T>
auto space_transformation (const Triangle<Point_3D<T>> &tr_1, const Triangle<Point_3D<T>> &tr_2)
{
    using triangle_2d = Triangle<Point_2D<T>>;
    using triangle_pair = std::pair<triangle_2d, triangle_2d>;
    
    auto [origin, x_axis, y_axis] = get_2d_coordinates (tr_1);

    triangle_2d new_tr_1 {Point_2D<T>{},
                          point_transformation (tr_1.Q(), origin, x_axis, y_axis),
                          point_transformation (tr_1.R(), origin, x_axis, y_axis)};

    triangle_2d new_tr_2 {point_transformation (tr_2.P(), origin, x_axis, y_axis),
                          point_transformation (tr_2.Q(), origin, x_axis, y_axis),
                          point_transformation (tr_2.R(), origin, x_axis, y_axis)};

    return triangle_pair{new_tr_1, new_tr_2};
}

template<typename T>
auto space_transformation (const Triangle<Point_3D<T>> &tr, const Point_3D<T> &pt)
{
    using point_2d = Point_2D<T>;
    using triangle_2d = Triangle<point_2d>;
    using point_triangle_pair = std::pair<point_2d, triangle_2d>;
    
    auto [origin, x_axis, y_axis] = get_2d_coordinates (tr);

    point_2d new_pt = point_transformation (pt, origin, x_axis, y_axis);

    triangle_2d new_tr {Point_2D<T>{},
                        point_transformation (tr.Q(), origin, x_axis, y_axis),
                        point_transformation (tr.R(), origin, x_axis, y_axis)};

    return point_triangle_pair{new_pt, new_tr};
}

template<typename T>
auto space_transformation (const Point_3D<T> &pt, const Triangle<Point_3D<T>> &tr)
{
    return space_transformation (tr, pt);
}

template<typename T>
auto space_transformation (const Triangle<Point_3D<T>> &tr, const Segment<Point_3D<T>> &seg)
{
    using segment_2d = Segment<Point_2D<T>>;
    using triangle_2d = Triangle<Point_2D<T>>;
    using segment_triangle_pair = std::pair<segment_2d, triangle_2d>;
    
    auto [origin, x_axis, y_axis] = get_2d_coordinates (tr);

    segment_2d new_seg {point_transformation (seg.P(), origin, x_axis, y_axis),
                        point_transformation (seg.Q(), origin, x_axis, y_axis)};

    triangle_2d new_tr {Point_2D<T>{},
                        point_transformation (tr.Q(), origin, x_axis, y_axis),
                        point_transformation (tr.R(), origin, x_axis, y_axis)};

    return segment_triangle_pair{new_seg, new_tr};
}

template<typename T>
auto space_transformation (const Segment<Point_3D<T>> &seg, const Triangle<Point_3D<T>> &tr)
{
    return space_transformation (tr, seg);
}

template<typename T>
auto space_transformation (const Segment<Point_3D<T>> &seg_1, const Segment<Point_3D<T>> &seg_2)
{
    using segment_2d = Segment<Point_2D<T>>;
    using segment_pair = std::pair<segment_2d, segment_2d>;

    // Think how to substitute following code with get_2d_axes()
    // =========================================================
    Vector<T> x_axis {seg_1.P(), seg_1.Q()};
    Vector<T> z_axis = vector_product (x_axis, Vector<T>{seg_2.P(), seg_2.Q()});
    Vector<T> y_axis = vector_product (z_axis, x_axis);

    x_axis.normalize();
    y_axis.normalize();
    // =========================================================

    segment_2d new_seg_1 {Point_2D<T>{}, 
                          point_transformation (seg_1.Q(), seg_1.P(), x_axis, y_axis)};

    segment_2d new_seg_2 {point_transformation (seg_2.P(), seg_1.P(), x_axis, y_axis),
                          point_transformation (seg_2.Q(), seg_1.P(), x_axis, y_axis)};

    return segment_pair{new_seg_1, new_seg_2};
}

} // namespace detail

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECION_SPACE_TO_PLANE_HPP
