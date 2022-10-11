#ifndef INCLUDE_TRIANGLE_HPP
#define INCLUDE_TRIANGLE_HPP

#include "point.hpp"
#include "double_comparison.hpp"

#include <algorithm> // for std::swap

namespace Geom_Objects
{

struct Triangle
{
    Point P_, Q_, R_;

    Triangle (const Point &P, const Point &Q, const Point &R) : P_ {P}, Q_ {Q}, R_ {R} {}

    void swap_QR () { std::swap (Q_, R_); }

    void swap_clockwise ()
    {
        std::swap (P_, R_);
        std::swap (Q_, R_);
    }

    void swap_counterclockwise ()
    {
        std::swap (P_, Q_);
        std::swap (R_, Q_);
    }
};

} // namespace Geom_Objects

#endif // INCLUDE_TRIANGLE_HPP
