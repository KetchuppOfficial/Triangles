#ifndef INCLUDE_INTERSECTION_3D_HPP
#define INCLUDE_INTERSECTION_3D_HPP

#include <utility>

#include "triangle.hpp"

#include "magic_product.hpp"
#include "space_to_plane.hpp"
#include "intersection_2D.hpp"

namespace yLab::geometry
{

namespace detail
{

template<typename T>
auto transform_triangle (const Triangle<Point_3D<T>> &tr_1_, Loc_3D P1_loc, Loc_3D Q1_loc, Loc_3D R1_loc, 
                         const Triangle<Point_3D<T>> &tr_2_)
{
    auto triangle_pair = std::make_pair (tr_1_, tr_2_);
    auto &tr_1 = triangle_pair.first;
    auto &tr_2 = triangle_pair.second;

    if (P1_loc == Loc_3D::Above)
    {
        if (Q1_loc == Loc_3D::Above && R1_loc != Loc_3D::Above)
        {
            tr_1.swap_clockwise();
            tr_2.swap_QR();
        }
        else if (Q1_loc != Loc_3D::Above && R1_loc == Loc_3D::Above)
        {
            tr_1.swap_counterclockwise();
            tr_2.swap_QR();
        }
    }
    else if (P1_loc == Loc_3D::On)
    {
        if (Q1_loc == Loc_3D::Above && R1_loc == Loc_3D::Above)
            tr_2.swap_QR();
        else if (Q1_loc == Loc_3D::Above && R1_loc != Loc_3D::Above)
            tr_1.swap_counterclockwise();
        else if (Q1_loc != Loc_3D::Above && R1_loc == Loc_3D::Above)
            tr_1.swap_clockwise();
        else if (Q1_loc == Loc_3D::On && R1_loc == Loc_3D::Below)
        {
            tr_1.swap_clockwise();
            tr_2.swap_QR();
        }
        else if (Q1_loc == Loc_3D::Below && R1_loc == Loc_3D::On)
        {
            tr_1.swap_counterclockwise();
            tr_2.swap_QR();
        }
    }
    else
    {
        if (Q1_loc == R1_loc)
            tr_2.swap_QR();
        else if (Q1_loc == Loc_3D::Below && R1_loc != Loc_3D::Below)
            tr_1.swap_clockwise();
        else if (Q1_loc != Loc_3D::Below && R1_loc == Loc_3D::Below)
            tr_1.swap_counterclockwise();
        else
            tr_2.swap_QR();
    }

    return triangle_pair;
}

template<typename T>
bool are_intersecting_3D (const Triangle<Point_3D<T>> &tr_1, const Triangle<Point_3D<T>> &tr_2,
                          Loc_3D P1_loc, Loc_3D Q1_loc, Loc_3D R1_loc)
{   
    auto P2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.P());
    auto Q2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.Q());
    auto R2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.R());

    if (P2_loc == Q2_loc && Q2_loc == R2_loc)
        return false;
    else
    {        
        // "m" means "modified"
        auto [tr_1m_, tr_2m_] = transform_triangle (tr_1, P1_loc, Q1_loc, R1_loc, tr_2);
        auto [tr_2m, tr_1m] = transform_triangle (tr_2m_, P2_loc, Q2_loc, R2_loc, tr_1m_);

        auto new_P1_loc = magic_product (tr_2m.P(), tr_2m.Q(), tr_2m.R(), tr_1m.P());
        auto new_P2_loc = magic_product (tr_1m.P(), tr_1m.Q(), tr_1m.R(), tr_2m.P());

        if (new_P1_loc == Loc_3D::On && new_P2_loc == Loc_3D::On)
            return (tr_1m.P() == tr_2m.P());
        else
        {
            auto KJ_mut_pos = magic_product (tr_1m.P(), tr_1m.Q(), tr_2m.P(), tr_2m.Q());
            auto LI_mut_pos = magic_product (tr_1m.P(), tr_1m.R(), tr_2m.P(), tr_2m.R());

            return (LI_mut_pos != Loc_3D::Below && KJ_mut_pos != Loc_3D::Above);
        }
    }
}

} // namespace detail

template<typename T>
bool are_intersecting (const Triangle<Point_3D<T>> &tr_1, const Triangle<Point_3D<T>> &tr_2)
{    
    using detail::Loc_2D;
    using detail::Loc_3D;
    using detail::magic_product;
    
    auto P1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
    auto Q1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.Q());
    auto R1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.R());

    if (P1_loc == Q1_loc && Q1_loc == R1_loc)
    {
        if (P1_loc == Loc_3D::On)
        {
            auto [tr_1_2d, tr_2_2d] = detail::space_transformation (tr_1, tr_2);

            if (magic_product (tr_1_2d.P(), tr_1_2d.Q(), tr_1_2d.R()) != Loc_2D::Positive)
                tr_1_2d.swap_QR();
            
            if (magic_product (tr_2_2d.P(), tr_2_2d.Q(), tr_2_2d.R()) != Loc_2D::Positive)
                tr_2_2d.swap_QR ();
            
            return detail::are_intersecting_2D (tr_1_2d, tr_2_2d);
        }
        else
            return false;
    }
    else
        return detail::are_intersecting_3D (tr_1, tr_2, P1_loc, Q1_loc, R1_loc);
}

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_3D_HPP
