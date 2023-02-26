#ifndef INCLUDE_INTERSECTION_SEGMENT_TRIANGLE_HPP
#define INCLUDE_INTERSECTION_SEGMENT_TRIANGLE_HPP

#include "segment.hpp"
#include "triangle.hpp"

#include "magic_product.hpp"
#include "space_to_plane.hpp"
#include "intersection_2D.hpp"

namespace yLab::geometry
{

template<typename T>
bool are_intersecting (const Segment<Point_3D<T>> &seg, const Triangle<Point_3D<T>> &tr)
{
    using detail::Loc_2D;
    using detail::Loc_3D;
    using detail::magic_product;

    auto P1_loc = magic_product (tr.P(), tr.Q(), tr.R(), seg.P());
    auto Q1_loc = magic_product (tr.P(), tr.Q(), tr.R(), seg.Q());

    if (P1_loc == Q1_loc)
    {
        if (P1_loc == Loc_3D::On)
        {
            auto [seg_2d, tr_2d] = detail::space_transformation (seg, tr);

            if (magic_product (tr_2d.P(), tr_2d.Q(), tr_2d.R()) != Loc_2D::Positive)
                tr_2d.swap_QR();

            return detail::are_intersecting_2D (tr_2d, seg_2d);
        }
        else
            return false;
    }
    else
    {
        auto seg_copy = seg;
        if (magic_product (tr.P(), tr.Q(), tr.R(), seg_copy.Q()) != Loc_3D::Below)
            seg_copy.swap_points();

        return (magic_product (seg_copy.P(), tr.P(), tr.Q(), seg_copy.Q()) != Loc_3D::Above &&
                magic_product (seg_copy.P(), tr.Q(), tr.R(), seg_copy.Q()) != Loc_3D::Above &&
                magic_product (seg_copy.P(), tr.R(), tr.P(), seg_copy.Q()) != Loc_3D::Above);
    }
}

template<typename T>
bool are_intersecting (const Triangle<Point_3D<T>> &tr, const Segment<Point_3D<T>> &seg)
{
    return are_intersecting (seg, tr);
}

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_SEGMENT_TRIANGLE_HPP
