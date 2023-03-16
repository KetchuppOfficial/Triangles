#ifndef INCLUDE_INTERSECTION_MAGIC_PRODUCT_HPP
#define INCLUDE_INTERSECTION_MAGIC_PRODUCT_HPP

#include "double_comparison.hpp"
#include "point.hpp"

namespace yLab::geometry
{

namespace detail
{

enum class Loc_2D
{
    Negative = -1,
    Neutral  = 0,
    Positive = 1
};

/*
 * Let P, Q, M be three points in R^2.
 *
 * Then magic_product(P, Q, M) is:
 * positive if P, Q, M (in this very order) locate in counterclockwise order,
 * negative if P, Q, M (in this very order) locate in clockwise order,
 * neutral if P, Q, M locate on the same line.
 */
template<typename T>
Loc_2D magic_product (const Point_2D<T> &P, const Point_2D<T> &Q, const Point_2D<T> &M)
{
    auto product = (P.x() - M.x()) * (Q.y() - M.y()) - (P.y() - M.y()) * (Q.x() - M.x());
    
    if (cmp::is_zero (product))
        return Loc_2D::Neutral;
    else if (cmp::greater (product, T{}))
        return Loc_2D::Positive;
    else
        return Loc_2D::Negative;
}

enum class Loc_3D
{
    Below = -1,
    On    = 0,
    Above = 1
};

/*
 * Let P, Q, R (in this very order) and M be points in R^3.
 *
 * Then magic_product(P, Q, R, M) is prcisely the sign of
 * triple product (v_PM, v_QM, v_RM), where 
 * v_PM is a vector with initial point P and terminal point M, 
 * v_QM is a vector with initial point Q and terminal point M,
 * v_RM is a vector with initial point R and terminal point M.
 */
template<typename T>
Loc_3D magic_product (const Point_3D<T> &P, const Point_3D<T> &Q, 
                      const Point_3D<T> &R, const Point_3D<T> &M)
{
    auto elem_21 = M.x() - Q.x();
    auto elem_22 = M.y() - Q.y();
    auto elem_23 = M.z() - Q.z();

    auto elem_31 = M.x() - R.x();
    auto elem_32 = M.y() - R.y();
    auto elem_33 = M.z() - R.z();

    auto product = (M.x() - P.x()) * (elem_22 * elem_33 - elem_23 * elem_32) -
                   (M.y() - P.y()) * (elem_21 * elem_33 - elem_23 * elem_31) +
                   (M.z() - P.z()) * (elem_21 * elem_32 - elem_22 * elem_31);

    if (cmp::is_zero (product))
        return Loc_3D::On;
    else if (cmp::greater (product, T{}))
        return Loc_3D::Above;
    else
        return Loc_3D::Below;
}

} // namespace detail

} // namespace yLab::geometry

#endif // INCLUDE_INTERSECTION_MAGIC_PRODUCT_HPP
