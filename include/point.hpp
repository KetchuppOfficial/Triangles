#ifndef INCLUDE_POINT_HPP
#define INCLUDE_POINT_HPP

#include <iostream>
#include <cmath> // for std::sqrt

#include "double_comparison.hpp"

namespace Geom_Objects
{

struct Point
{
    double x_, y_, z_;

    Point (const double x = 0.0, const double y = 0.0, const double z = 0.0)
          : x_{x}, y_{y}, z_{z} {}

    bool operator== (const Point &other) const
    {
        return (cmp::are_equal (x_, other.x_) &&
                cmp::are_equal (y_, other.y_) &&
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

        return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    }
}

} // namespace Geom_Objects

#endif // INCLUDE_POINT_HPP
