#ifndef INCLUDE_PRIMITIVES_POINT_HPP
#define INCLUDE_PRIMITIVES_POINT_HPP

#include <cmath>
#include <ostream>
#include <type_traits>

#include "double_comparison.hpp"

namespace yLab
{

namespace geometry
{

template <typename T>
requires std::is_floating_point_v<T>
struct Point_2D final
{
    T x_, y_;

    explicit Point_2D (T x = T{}, T y = T{}) : x_ {x}, y_ {y} {}

    bool operator== (const Point_2D &other) const
    {
        return (cmp::are_equal (x_, other.x_) && cmp::are_equal (y_, other.y_));
    }

    bool is_valid () const { return (x_ == x_ && y_ == y_); }
};

template<typename T>
T distance (const Point_2D<T> &first, const Point_2D<T> &second)
{
    if (first == second)
        return T{};
    else
    {
        auto x_diff = first.x_ - second.x_;
        auto y_diff = first.y_ - second.y_;

        return std::sqrt (x_diff * x_diff + y_diff * y_diff);
    }
}

template<typename T>
void dump (std::ostream &os, const Point_2D<T> &pt)
{
    os << "(" << pt.x_ << ", " << pt.y_ << ")";
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const Point_2D<T> &pt)
{
    dump (os, pt);
    return os;
}

template <typename T>
requires std::is_floating_point_v<T>
struct Point_3D final
{
    T x_, y_, z_;

    explicit Point_3D (T x = T{}, T y = T{}, T z = T{}) : x_ {x}, y_ {y}, z_ {z} {}

    bool operator== (const Point_3D &other) const
    {
        return (cmp::are_equal (x_, other.x_) && cmp::are_equal (y_, other.y_) &&
                cmp::are_equal (z_, other.z_));
    }

    bool is_valid () const { return (x_ == x_ && y_ == y_ && z_ == z_); }
};

template<typename T>
T distance (const Point_3D<T> &first, const Point_3D<T> &second)
{
    if (first == second)
        return T{};
    else
    {
        auto x_diff = first.x_ - second.x_;
        auto y_diff = first.y_ - second.y_;
        auto z_diff = first.z_ - second.z_;

        return std::sqrt (x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    }
}

template<typename T>
void dump (std::ostream &os, const Point_3D<T> &pt)
{
    os << "(" << pt.x_ << ", " << pt.y_ << ", " << pt.z_ << ")";
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const Point_3D<T> &pt)
{
    dump (os, pt);
    return os;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_POINT_HPP
