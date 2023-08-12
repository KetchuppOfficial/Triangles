#ifndef INCLUDE_INTERSECTION_SEGMENT_SEGMENT_HPP
#define INCLUDE_INTERSECTION_SEGMENT_SEGMENT_HPP

#include "segment.hpp"
#include "vector.hpp"

#include "magic_product.hpp"
#include "space_to_plane.hpp"

namespace yLab::geometry
{

template<typename T>
bool are_intersecting (const Segment<Point_3D<T>> &seg_1, const Segment<Point_3D<T>> &seg_2)
{
    using detail::magic_product;

    Vector P1_Q1{seg_1.P(), seg_1.Q()};
    Vector P2_Q2{seg_2.P(), seg_2.Q()};
    Vector P1_Q2{seg_1.P(), seg_2.Q()};

    if (!are_coplanar (P1_Q1, P2_Q2, P1_Q2))
        return false;
    else if (are_collinear (P1_Q1, P2_Q2))
    {
        if (are_collinear (P1_Q1, P1_Q2))
        {
            Vector P2_Q1{seg_2.P(), seg_1.Q()};

            if (are_codirectional (P1_Q1, P2_Q2))
                return are_codirectional (P1_Q2, P2_Q1);
            else
                return are_oppositely_directed (P1_Q2, P2_Q1);
        }
        else
            return false;
    }
    else
    {
        auto [seg_1_2d, seg_2_2d] = detail::space_transformation (seg_1, seg_2);

        auto P2_wrt_P1Q1 = magic_product (seg_1_2d.P(), seg_1_2d.Q(), seg_2_2d.P());
        auto Q2_wrt_P1Q1 = magic_product (seg_1_2d.P(), seg_1_2d.Q(), seg_2_2d.Q());

        auto mult_1 = static_cast<int>(P2_wrt_P1Q1) * static_cast<int>(Q2_wrt_P1Q1);

        if (mult_1 > 0)
            return false;
        else
        {
            auto P1_wrt_P2Q2 = magic_product (seg_2_2d.P(), seg_2_2d.Q(), seg_1_2d.P());
            auto Q1_wrt_P2Q2 = magic_product (seg_2_2d.P(), seg_2_2d.Q(), seg_1_2d.Q());

            auto mult_2 = static_cast<int>(P1_wrt_P2Q2) * static_cast<int>(Q1_wrt_P2Q2);

            return mult_2 <= 0;
        }
    }
}

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_SEGMENT_SEGMENT_HPP
