#ifndef INCLUDE_POINT_HPP
#define INCLUDE_POINT_HPP

#include "double_comparison.hpp"

#include <cmath> // for std::sqrt
#include <iostream>

namespace Geom_Objects
{

struct Point
{
    double x_, y_, z_;

    Point (const double x = 0.0, const double y = 0.0, const double z = 0.0)
        : x_ {x}, y_ {y}, z_ {z}
    {}

    bool operator== (const Point &other) const
    {
        return (cmp::are_equal (x_, other.x_) && cmp::are_equal (y_, other.y_) &&
                cmp::are_equal (z_, other.z_));
    }

    bool operator!= (const Point &other) const { return !(*this == other); }

    bool is_valid () const { return (x_ == x_ && y_ == y_ && z_ == z_); }

    void print () const { std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl; }
};

inline double distance (const Point &first, const Point &second)
{
    if (first == second)
        return 0.0;
    else
    {
        auto x_diff = first.x_ - second.x_;
        auto y_diff = first.y_ - second.y_;
        auto z_diff = first.z_ - second.z_;

        return std::sqrt (x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    }
}

enum class Loc_3D
{
    Below = -1,
    On    = 0,
    Above = 1
};

enum Loc_2D
{
    Negative = -1,
    Neutral  = 0,
    Positive = 1,
    Is_vertice = 1,
    On_side = 2
};

/*
 * Let P, Q, R (in this very order) and M be points in R^3.
 *
 * Then magic_product(P, Q, R, M) is prcisely the sign of
 * triple product (v_PM, v_QM, v_RM), where v_PM is a vector
 * with initial point P and terminal point M, v_QM - vector
 * with initial point Q and terminal point M, v_RM - vector
 * with initial point R and terminal point M.
 */
inline Loc_3D magic_product (const Point &P, const Point &Q, const Point &R, const Point &M)
{
    auto elem_21 = M.x_ - Q.x_;
    auto elem_22 = M.y_ - Q.y_;
    auto elem_23 = M.z_ - Q.z_;

    auto elem_31 = M.x_ - R.x_;
    auto elem_32 = M.y_ - R.y_;
    auto elem_33 = M.z_ - R.z_;

    auto product = (M.x_ - P.x_) * (elem_22 * elem_33 - elem_23 * elem_32) -
                   (M.y_ - P.y_) * (elem_21 * elem_33 - elem_23 * elem_31) +
                   (M.z_ - P.z_) * (elem_21 * elem_32 - elem_22 * elem_31);

    if (cmp::are_equal (product, 0.0))
        return Loc_3D::On;
    else if (product > 0)
        return Loc_3D::Above;
    else
        return Loc_3D::Below;
}

inline Loc_2D magic_product (const Point &P, const Point &Q, const Point &M)
{
    auto product = (P.x_ - M.x_) * (Q.y_ - M.y_) - (P.y_ - M.y_) * (Q.x_ - M.x_);
    //  Positive product is considered when points locate in counterclockwise ordering
    if (cmp::are_equal (product, 0.0))
        return Loc_2D::Neutral;
    else if (product > 0)
        return Loc_2D::Positive;
    else
        return Loc_2D::Negative;
}

} // namespace Geom_Objects

#endif // INCLUDE_POINT_HPP
