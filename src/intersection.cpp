#include "intersection.hpp"
#include "point.hpp"

#define ALGORITHM_TESTING

namespace Geom_Objects
{

#ifndef ALGORITHM_TESTING
namespace
{
#endif // ALGORITHM_TESTING

bool intersection_in_2d (const Triangle &tr_1, const Triangle &tr_2)
{
    std::cout << "2D intersection is not implemented yet" << std::endl;
    return false;
}

void transform_triangle (Triangle &tr_1, const Loc_3D P1_loc, const Loc_3D Q1_loc, const Loc_3D R1_loc, Triangle &tr_2)
{
    if (P1_loc == Loc_3D::Above)
    {
        if (Q1_loc == Loc_3D::Above && R1_loc != Loc_3D::Above)
        {
            tr_1.swap_clockwise ();
            tr_2.swap_QR ();
        }
        else if (Q1_loc != Loc_3D::Above && R1_loc == Loc_3D::Above)
        {
            tr_1.swap_counterclockwise ();
            tr_2.swap_QR ();
        }
    }
    else if (P1_loc == Loc_3D::On)
    {
        if (Q1_loc == Loc_3D::Above && R1_loc == Loc_3D::Above)
            tr_2.swap_QR ();
        else if (Q1_loc == Loc_3D::Above && R1_loc != Loc_3D::Above)
            tr_1.swap_counterclockwise ();
        else if (Q1_loc != Loc_3D::Above && R1_loc == Loc_3D::Above)
            tr_1.swap_clockwise ();
        else if (Q1_loc == Loc_3D::On && R1_loc == Loc_3D::Below)
        {
            tr_1.swap_clockwise ();
            tr_2.swap_QR ();
        }
        else if (Q1_loc == Loc_3D::Below && R1_loc == Loc_3D::On)
        {
            tr_1.swap_counterclockwise ();
            tr_2.swap_QR ();
        }
    }
    else
    {
        if (Q1_loc == R1_loc)
            tr_2.swap_QR ();
        else if (Q1_loc == Loc_3D::Below && R1_loc != Loc_3D::Below)
            tr_1.swap_clockwise ();
        else if (Q1_loc != Loc_3D::Below && R1_loc == Loc_3D::Below)
            tr_1.swap_counterclockwise ();
        else
            tr_2.swap_QR ();
    }
}

bool intersection_in_3D (const Triangle &tr_1_, const Triangle &tr_2_, const Loc_3D P1_loc,
                         const Loc_3D Q1_loc, const Loc_3D R1_loc)
{
    Triangle tr_1 = tr_1_;
    Triangle tr_2 = tr_2_;
    
    auto P2_loc = magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.P_);
    auto Q2_loc = magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.Q_);
    auto R2_loc = magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.R_);

    if (P2_loc != Loc_3D::On && P2_loc == Q2_loc && Q2_loc == R2_loc)
        return false;
    else
    {
        transform_triangle (tr_1, P1_loc, Q1_loc, R1_loc, tr_2);
        transform_triangle (tr_2, P2_loc, Q2_loc, R2_loc, tr_1);

        auto new_P1_loc = magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.P_);
        auto new_P2_loc = magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.P_);

        if (new_P1_loc == Loc_3D::On && new_P2_loc == Loc_3D::On)
            return (tr_1.P_ == tr_2.P_);
        else
        {
            auto KJ_mut_pos = magic_product (tr_1.P_, tr_1.Q_, tr_2.P_, tr_2.Q_);
            auto LI_mut_pos = magic_product (tr_1.P_, tr_1.R_, tr_2.P_, tr_2.R_);

            return (LI_mut_pos != Loc_3D::Below && KJ_mut_pos != Loc_3D::Above);
        }
    }
}

#ifndef ALGORITHM_TESTING
} // anonymous namespace
#endif // ALGORITHM_TESTING

bool are_intersecting (const Triangle &tr_1, const Triangle &tr_2)
{
    auto P1_loc = magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.P_);
    auto Q1_loc = magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.Q_);
    auto R1_loc = magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.R_);

    if (P1_loc != Loc_3D::On && P1_loc == Q1_loc && Q1_loc == R1_loc)
        return false;
    else if (P1_loc == Loc_3D::On && Q1_loc == Loc_3D::On && R1_loc == Loc_3D::On)
        return intersection_in_2d (tr_1, tr_2);
    else
        return intersection_in_3D (tr_1, tr_2, P1_loc, Q1_loc, R1_loc);
}

} // namespace Geom_Objects
