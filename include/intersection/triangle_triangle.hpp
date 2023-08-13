#ifndef INCLUDE_INTERSECTION_3D_HPP
#define INCLUDE_INTERSECTION_3D_HPP

#include <utility>
#include <tuple>

#include "triangle.hpp"

#include "magic_product.hpp"
#include "space_to_plane.hpp"
#include "intersection_2D.hpp"

namespace yLab::geometry
{

namespace detail
{

template<typename T>
std::tuple<Loc_3D, Loc_3D, Loc_3D> compute_relative_location (const Triangle<Point_3D<T>> &tr_1,
                                                              const Triangle<Point_3D<T>> &tr_2)
{
    auto P1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
    auto Q1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.Q());
    auto R1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.R());

    return std::tuple{P1_loc, Q1_loc, R1_loc};
}

// P2_loc doesn't change; Q2_loc and R2_loc don't change or they are swapped
template<typename T>
auto transform_triangles (Triangle<Point_3D<T>> &tr_1, Loc_3D P1_loc, Loc_3D Q1_loc, Loc_3D R1_loc,
                          Triangle<Point_3D<T>> &tr_2)
{
    switch (P1_loc)
    {
        case Loc_3D::Above:

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

            break;

        case Loc_3D::On:

            if (Q1_loc == Loc_3D::Above)
            {
                if (R1_loc == Loc_3D::Above)
                    tr_2.swap_QR();
                else
                    tr_1.swap_counterclockwise();
            }
            else if (R1_loc == Loc_3D::Above)
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

            break;

        case Loc_3D::Below:

            if (Q1_loc == R1_loc)
                tr_2.swap_QR();
            else if (Q1_loc == Loc_3D::Below)
                tr_1.swap_clockwise();
            else if (R1_loc == Loc_3D::Below)
                tr_1.swap_counterclockwise();
            else
                tr_2.swap_QR();

            break;
    }
}

template<typename T>
bool are_intersecting_3D (Triangle<Point_3D<T>> tr_1, Triangle<Point_3D<T>> tr_2,
                          Loc_3D P1_loc, Loc_3D Q1_loc, Loc_3D R1_loc)
{
    auto [P2_loc, Q2_loc, R2_loc] = detail::compute_relative_location (tr_2, tr_1);

    if (P2_loc == Q2_loc && Q2_loc == R2_loc)
        return false;
    else
    {
        transform_triangles (tr_1, P1_loc, Q1_loc, R1_loc, tr_2);
        P1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
        Q2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.Q());
        R2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.R());

        transform_triangles (tr_2, P2_loc, Q2_loc, R2_loc, tr_1);
        P2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.P());

        if (P1_loc == Loc_3D::On && P2_loc == Loc_3D::On)
            return (tr_1.P() == tr_2.P());
        else
        {
            auto KJ_mut_pos = magic_product (tr_1.P(), tr_1.Q(), tr_2.P(), tr_2.Q());
            auto LI_mut_pos = magic_product (tr_1.P(), tr_1.R(), tr_2.P(), tr_2.R());

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

    auto [P1_loc, Q1_loc, R1_loc] = detail::compute_relative_location (tr_1, tr_2);

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
