#include "intersection.hpp"
#include "point.hpp"
#include "vector.hpp"

#define ALGORITHM_TESTING

namespace Geom_Objects
{

#ifndef ALGORITHM_TESTING
namespace
{
#endif // ALGORITHM_TESTING

void point_transformation (Point &point, const Point &origin, const Vector &x_axis,
                           const Vector &y_axis)
{
    auto diff_x = point.x_ - origin.x_;
    auto diff_y = point.y_ - origin.y_;
    auto diff_z = point.z_ - origin.z_;

    point.x_ = x_axis.x_ * diff_x + x_axis.y_ * diff_y + x_axis.z_ * diff_z;
    point.y_ = y_axis.x_ * diff_x + y_axis.y_ * diff_y + y_axis.z_ * diff_z;
    point.z_ = 0.0;
}

void space_transformation (Triangle &tr_1, Triangle &tr_2)
{
    Vector x_axis {tr_1.P_, tr_1.Q_};
    x_axis *= (1 / x_axis.module ());

    Vector normal = vector_product (Vector {tr_1.P_, tr_1.Q_}, Vector {tr_1.P_, tr_1.R_});
    normal *= (1 / normal.module ());

    Vector y_axis = vector_product (normal, x_axis);

    point_transformation (tr_1.Q_, tr_1.P_, x_axis, y_axis);
    point_transformation (tr_1.R_, tr_1.P_, x_axis, y_axis);

    point_transformation (tr_2.P_, tr_1.P_, x_axis, y_axis);
    point_transformation (tr_2.Q_, tr_1.P_, x_axis, y_axis);
    point_transformation (tr_2.R_, tr_1.P_, x_axis, y_axis);
    tr_1.P_ = {0.0, 0.0, 0.0}; //  this is origin
}

bool test_intersection_R1 (const Triangle &tr_1, const Triangle &tr_2)
{
    if (magic_product (tr_2.R_, tr_2.P_, tr_1.Q_) == Loc_2D::Negative)
    {
        return !(magic_product (tr_2.R_, tr_2.P_, tr_1.R_) == Loc_2D::Negative ||
                 magic_product (tr_1.Q_, tr_1.R_, tr_2.R_) == Loc_2D::Negative ||
                 magic_product (tr_1.P_, tr_2.P_, tr_1.R_) == Loc_2D::Negative);
    }
    else 
    {
        if (magic_product (tr_2.R_, tr_1.P_, tr_1.Q_) == Loc_2D::Negative)
            return false;
        else if (magic_product (tr_1.P_, tr_2.P_, tr_1.Q_) != Loc_2D::Negative)
            return true;
        else if ((magic_product (tr_1.P_, tr_2.P_, tr_1.R_) == Loc_2D::Negative) ||
                 (magic_product (tr_1.Q_, tr_1.R_, tr_2.P_) == Loc_2D::Negative))
            return false;
        else
            return true;
    }
}

bool test_intersection_R2 (const Triangle &tr_1, const Triangle &tr_2)
{
    if (magic_product (tr_2.R_, tr_2.P_, tr_1.Q_) == Loc_2D::Negative)
    {
        if (magic_product (tr_2.R_, tr_2.P_, tr_1.R_) == Loc_2D::Negative)
            return false;
        else if (magic_product (tr_1.Q_, tr_1.R_, tr_2.R_) == Loc_2D::Negative)
        {
            return !(magic_product (tr_1.Q_, tr_1.R_, tr_2.Q_) == Loc_2D::Negative ||
                     magic_product (tr_2.Q_, tr_2.R_, tr_1.R_) == Loc_2D::Negative);
        }
        else
            return !(magic_product (tr_1.R_, tr_1.P_, tr_2.P_) == Loc_2D::Negative);
    }
    else
    {
        if (magic_product (tr_2.Q_, tr_2.R_, tr_1.Q_) == Loc_2D::Negative)
        {
            return !(magic_product (tr_1.P_, tr_2.Q_, tr_1.Q_) == Loc_2D::Positive ||
                     magic_product (tr_2.Q_, tr_2.R_, tr_1.R_) == Loc_2D::Negative ||
                     magic_product (tr_1.Q_, tr_1.R_, tr_2.Q_) == Loc_2D::Negative);
        }
        else
        {
            if (magic_product (tr_1.P_, tr_2.P_, tr_1.Q_) == Loc_2D::Negative)
            {
                return !(magic_product (tr_1.P_, tr_2.P_, tr_1.R_) == Loc_2D::Negative ||
                         magic_product (tr_2.R_, tr_2.P_, tr_1.R_) == Loc_2D::Negative);
            }
            else 
                return !(magic_product (tr_1.P_, tr_2.Q_, tr_1.Q_) == Loc_2D::Positive);
        }
    }
}

bool intersection_in_2D (const Triangle &tr_1_, const Triangle &tr_2_)
{
    Triangle tr_1 = tr_1_;
    Triangle tr_2 = tr_2_;
    space_transformation (tr_1, tr_2);

    //  if swap tr_2.Q_ and tr_2.R_
    if (magic_product (tr_2.P_, tr_2.Q_, tr_2.R_) == Loc_2D::Negative)
        tr_2.swap_QR ();

    auto P1_P2_Q2 = magic_product (tr_2.P_, tr_2.Q_, tr_1.P_);
    auto P1_Q2_R2 = magic_product (tr_2.Q_, tr_2.R_, tr_1.P_);
    auto P1_R2_P2 = magic_product (tr_2.R_, tr_2.P_, tr_1.P_);
    auto P1_loc   = P1_P2_Q2 * P1_Q2_R2 * P1_R2_P2;

    //  interior of tr_2
    if (P1_P2_Q2 == Loc_2D::Positive &&
        P1_Q2_R2 == Loc_2D::Positive && 
        P1_R2_P2 == Loc_2D::Positive)
        return true;
    //  in vertice of tr_2
    else if ((P1_loc == Loc_2D::Neutral) &&
             (P1_P2_Q2 + P1_Q2_R2 + P1_R2_P2 == 1))
        return true;
    //  on side of tr_2
    else if ((P1_loc == Loc_2D::Neutral) &&
             (P1_P2_Q2 + P1_Q2_R2 + P1_R2_P2 == 2))
        return true;
    else if ((P1_loc == Loc_2D::Negative) ||
             ((P1_loc == Loc_2D::Neutral) &&
              (P1_P2_Q2 + P1_Q2_R2 + P1_R2_P2 == 0)))
        return test_intersection_R1 (tr_1, tr_2);
    else if (P1_loc == Loc_2D::Positive)
        return test_intersection_R2 (tr_1, tr_2);
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
        return intersection_in_2D (tr_1, tr_2);
    else
        return intersection_in_3D (tr_1, tr_2, P1_loc, Q1_loc, R1_loc);
}

} // namespace Geom_Objects
