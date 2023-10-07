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

template<typename T>
requires std::is_floating_point_v<T>
class Point_2D final
{
public:

    using distance_type = T;

private:

    distance_type coordinates_[2];

public:

    explicit Point_2D (T x = T{}, T y = T{}) : coordinates_{x, y} {}

    distance_type x () const { return coordinates_[0]; }
    distance_type y () const { return coordinates_[1]; }

    // No bound checking !!!
    distance_type operator[] (int i) const { return coordinates_[i]; }
    distance_type &operator[] (int i) { return coordinates_[i]; }

    bool is_valid () const { return !std::isnan(x()) && !std::isnan(y()); }
};

template<typename T>
bool operator== (const Point_2D<T> &lhs, const Point_2D<T> &rhs)
{
    return (cmp::are_equal (lhs.x(), rhs.x()) && cmp::are_equal (lhs.y(), rhs.y()));
}

template<typename T>
T distance (const Point_2D<T> &first, const Point_2D<T> &second)
{
    if (first == second)
        return T{};
    else
    {
        auto x_diff = first.x() - second.x();
        auto y_diff = first.y() - second.y();

        return std::sqrt (x_diff * x_diff + y_diff * y_diff);
    }
}

template<typename T>
void dump (std::ostream &os, const Point_2D<T> &pt)
{
    os << "(" << pt.x() << ", " << pt.y() << ")";
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const Point_2D<T> &pt)
{
    dump (os, pt);
    return os;
}

template<typename T>
requires std::is_floating_point_v<T>
class Point_3D final
{
public:

    using distance_type = T;

private:

    distance_type coordinates_[3];

public:

    explicit Point_3D (T x = T{}, T y = T{}, T z = T{}) : coordinates_{x, y, z} {}

    distance_type x () const { return coordinates_[0]; }
    distance_type y () const { return coordinates_[1]; }
    distance_type z () const { return coordinates_[2]; }

    // No bound checking !!!
    distance_type operator[] (int i) const { return coordinates_[i]; }
    distance_type &operator[] (int i) { return coordinates_[i]; }

    bool is_valid () const { return !std::isnan(x()) && !std::isnan(y()) && !std::isnan(z()); }
};

template<typename T>
bool operator== (const Point_3D<T> &lhs, const Point_3D<T> &rhs)
{
    return (cmp::are_equal (lhs.x(), rhs.x()) && cmp::are_equal (lhs.y(), rhs.y()) &&
            cmp::are_equal (lhs.z(), rhs.z()));
}

template<typename T>
T distance (const Point_3D<T> &first, const Point_3D<T> &second)
{
    if (first == second)
        return T{};
    else
    {
        auto x_diff = first.x() - second.x();
        auto y_diff = first.y() - second.y();
        auto z_diff = first.z() - second.z();

        return std::sqrt (x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    }
}

template<typename T>
void dump (std::ostream &os, const Point_3D<T> &pt)
{
    os << "(" << pt.x() << ", " << pt.y() << ", " << pt.z() << ")";
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
