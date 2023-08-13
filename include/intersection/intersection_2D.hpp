#ifndef INCLUDE_INTERSECTION_INTERSECTION_2D_HPP
#define INCLUDE_INTERSECTION_INTERSECTION_2D_HPP

#include <stdexcept>

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"

#include "magic_product.hpp"
#include "point_triangle.hpp"

namespace yLab::geometry
{

namespace detail
{

// Segment-triangle intersection

template<typename T>
bool test_intersection_R1 (const Segment<Point_2D<T>> &seg,
                           const Triangle<Point_2D<T>> &tr)
{
    if (magic_product (tr.R(), tr.P(), seg.Q()) == Loc_2D::Negative)
        return false;
    else
        return (magic_product (seg.P(), tr.P(), seg.Q()) != Loc_2D::Negative &&
                magic_product (seg.P(), tr.R(), seg.Q()) != Loc_2D::Positive);
}

template<typename T>
bool test_intersection_R2 (const Segment<Point_2D<T>> &seg,
                           const Triangle<Point_2D<T>> &tr)
{
    if (magic_product (tr.R(), tr.P(), seg.Q()) == Loc_2D::Negative)
        return false;
    else
    {
        return  (magic_product (seg.P(), tr.P(), seg.Q()) != Loc_2D::Negative &&
                 magic_product (seg.P(), tr.Q(), seg.Q()) != Loc_2D::Positive &&
                 magic_product (tr.Q(),  tr.R(), seg.Q()) != Loc_2D::Negative);
    }
}

// Triangle-triangle intersection

template<typename T>
bool test_intersection_R1 (const Triangle<Point_2D<T>> &tr_1,
                           const Triangle<Point_2D<T>> &tr_2)
{
    if (magic_product (tr_2.R(), tr_2.P(), tr_1.Q()) == Loc_2D::Negative) // Q1 belongs to R11
    {
        if (magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc_2D::Negative) // R1 belongs to R11
            return false;
        else
            return (magic_product (tr_1.Q(), tr_2.R(), tr_1.R()) != Loc_2D::Positive &&
                    magic_product (tr_1.P(), tr_2.P(), tr_1.R()) != Loc_2D::Negative);
    }
    else
    {
        if (magic_product (tr_1.P(), tr_2.R(), tr_1.Q()) == Loc_2D::Positive) // Q1 belongs to R12
            return false;
        else if (magic_product (tr_1.P(), tr_2.P(), tr_1.Q()) != Loc_2D::Negative) // Q1 belongs to R13
            return true;
        else // Q1 belongs to R14
            return (magic_product (tr_1.P(), tr_2.P(), tr_1.R()) != Loc_2D::Negative &&
                    magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) != Loc_2D::Positive);
    }
}

template<typename T>
bool test_intersection_R2 (const Triangle<Point_2D<T>> &tr_1,
                           const Triangle<Point_2D<T>> &tr_2)
{
    if (magic_product (tr_2.R(), tr_2.P(), tr_1.Q()) == Loc_2D::Negative) // Q1 in R21
    {
        if (magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc_2D::Negative) // R1 in R21
            return false;
        else if (magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) != Loc_2D::Negative)
            return magic_product (tr_1.P(), tr_2.P(), tr_1.R()) != Loc_2D::Negative;
        else
            return (magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) != Loc_2D::Negative &&
                    magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) != Loc_2D::Negative);
    }
    else if (magic_product (tr_2.Q(), tr_2.R(), tr_1.Q()) == Loc_2D::Negative) // Q1 in R22 or R25
    {
        if (magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Loc_2D::Negative) // Q1 in R25
        {
            return (magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) != Loc_2D::Negative &&
                    magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) != Loc_2D::Negative);
        }
        else
            return false;
    }
    else if (magic_product (tr_1.P(), tr_2.P(), tr_1.Q()) == Loc_2D::Negative) // Q1 in R24
    {
        return (magic_product (tr_1.P(), tr_2.P(), tr_1.R()) != Loc_2D::Negative &&
                magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) != Loc_2D::Positive);
    }
    else
        return magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) != Loc_2D::Positive;
}

template<typename T, typename Primitive_T>
bool are_intersecting_2D (Primitive_T &other, Triangle<Point_2D<T>> &tr)
{
    auto P1_wrt_P2Q2 = magic_product (tr.P(), tr.Q(), other.P());
    auto P1_wrt_Q2R2 = magic_product (tr.Q(), tr.R(), other.P());
    auto P1_wrt_R2P2 = magic_product (tr.R(), tr.P(), other.P());

    auto P1_loc = deduce_pt_location (P1_wrt_P2Q2, P1_wrt_Q2R2, P1_wrt_R2P2);

    switch (P1_loc)
    {
        case Pt_Wrt_Tr::Inside:
        case Pt_Wrt_Tr::In_Vertex:
        case Pt_Wrt_Tr::On_Side:

            return true;

        case Pt_Wrt_Tr::In_R1:

            if (P1_wrt_P2Q2 == Loc_2D::Negative)
                tr.swap_counterclockwise();
            else if (P1_wrt_Q2R2 == Loc_2D::Negative)
                tr.swap_clockwise();

            return test_intersection_R1 (other, tr);

        case Pt_Wrt_Tr::In_R2:

            if (P1_wrt_R2P2 == Loc_2D::Positive)
                tr.swap_clockwise();
            else if (P1_wrt_Q2R2 == Loc_2D::Positive)
                tr.swap_counterclockwise();

            return test_intersection_R2 (other, tr);

        default:
            throw std::runtime_error ("Something bad happened");
    }
}

} // namespace detail

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_INTERSECTION_2D_HPP
