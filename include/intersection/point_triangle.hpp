#ifndef INCLUDE_INTERSECTION_POINT_TRIANGLE_HPP
#define INCLUDE_INTERSECTION_POINT_TRIANGLE_HPP

#include <cassert>

#include "point.hpp"
#include "triangle.hpp"

#include "magic_product.hpp"
#include "space_to_plane.hpp"

namespace yLab::geometry
{

namespace detail
{

// Point with reference to triangle
enum class Pt_Wrt_Tr
{
    Inside,
    In_Vertex,
    On_Side,
    In_R1, // algorithm specific term
    In_R2  // algorithm specific term
};

inline constexpr Pt_Wrt_Tr deduce_pt_location (Loc_2D loc_1, Loc_2D loc_2, Loc_2D loc_3)
{
    if (loc_1 == Loc_2D::Positive &&
        loc_2 == Loc_2D::Positive &&
        loc_3 == Loc_2D::Positive)
        return Pt_Wrt_Tr::Inside;
    else
    {
        auto mult = static_cast<int>(loc_1) * static_cast<int>(loc_2) * static_cast<int>(loc_3);
        
        if (mult < 0)
            return Pt_Wrt_Tr::In_R1;
        else if (mult > 0)
            return Pt_Wrt_Tr::In_R2;
        else /* if (mult == 0) */
        {
            auto sum  = static_cast<int>(loc_1) + static_cast<int>(loc_2) + static_cast<int>(loc_3);

            if (sum == 0)
                return Pt_Wrt_Tr::In_R2; // point belongs to the boundary of R2
            if (sum == 1)
                return Pt_Wrt_Tr::In_Vertex;
            else /* if (sum == 2) */
                return Pt_Wrt_Tr::On_Side;
        }
    }
}

} // namespace detail

template<typename T>
bool are_intersecting (const Point_3D<T> &pt, const Triangle<Point_3D<T>> &tr)
{    
    using detail::Loc_3D;
    using detail::Pt_Wrt_Tr;
    using detail::magic_product;
    
    auto pt_loc = magic_product (tr.P(), tr.Q(), tr.R(), pt);

    if (pt_loc == Loc_3D::On)
    {
        auto [pt_2d, tr_2d] = detail::space_transformation (pt, tr);

        auto pt_wrt_PQ = magic_product (tr_2d.P(), tr_2d.Q(), pt_2d);
        auto pt_wrt_QR = magic_product (tr_2d.Q(), tr_2d.R(), pt_2d);
        auto pt_wrt_RP = magic_product (tr_2d.R(), tr_2d.P(), pt_2d);

        auto pt_loc = detail::deduce_pt_location (pt_wrt_PQ, pt_wrt_QR, pt_wrt_RP);
        
        return (pt_loc != Pt_Wrt_Tr::In_R1 && pt_loc != Pt_Wrt_Tr::In_R2);
    }
    else
        return false;
}

template<typename T>
bool are_intersecting (const Triangle<Point_3D<T>> &tr, const Point_3D<T> &pt)
{
    return are_intersecting (pt, tr);
}

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_POINT_TRIANGLE_HPP
