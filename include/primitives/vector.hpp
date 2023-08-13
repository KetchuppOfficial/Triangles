#ifndef INCLUDE_PRIMITIVES_VECTOR_HPP
#define INCLUDE_PRIMITIVES_VECTOR_HPP

#include <cmath>
#include <ostream>

#include "double_comparison.hpp"
#include "point.hpp"

namespace yLab
{

namespace geometry
{

template<typename T>
requires std::is_floating_point_v<T>
struct Vector final
{
    T x_, y_;
    T z_ = T{};

    explicit Vector (T x = T{}, T y = T{}, T z = T{}) : x_{x}, y_{y}, z_{z} {}

    Vector (const Point_3D<T> &pt) : x_ {pt.x()}, y_{pt.y()}, z_{pt.z()} {}

    Vector (const Point_3D<T> &first, const Point_3D<T> &second)
           : x_ {cmp::are_equal (first.x(), second.x()) ? T{} : second.x() - first.x()},
             y_ {cmp::are_equal (first.y(), second.y()) ? T{} : second.y() - first.y()},
             z_ {cmp::are_equal (first.z(), second.z()) ? T{} : second.z() - first.z()} {}

    Vector (const Point_2D<T> &first, const Point_2D<T> &second)
           : x_ {cmp::are_equal (first.x(), second.x()) ? T{} : second.x() - first.x()},
             y_ {cmp::are_equal (first.y(), second.y()) ? T{} : second.y() - first.y()} {}

    bool operator== (const Vector &other) const
    {
        return (cmp::are_equal (x_, other.x_) && cmp::are_equal (y_, other.y_) &&
                cmp::are_equal (z_, other.z_));
    }

    Vector &operator+= (const Vector &rhs)
    {
        x_ = cmp::are_equal (x_, -rhs.x_) ? T{} : x_ + rhs.x_;
        y_ = cmp::are_equal (y_, -rhs.y_) ? T{} : y_ + rhs.y_;
        z_ = cmp::are_equal (z_, -rhs.z_) ? T{} : z_ + rhs.z_;

        return *this;
    }

    Vector operator+ (const Vector &other) const
    {
        Vector sum = *this;
        return (sum += other);
    }

    Vector &operator-= (const Vector &rhs)
    {
        x_ = cmp::are_equal (x_, rhs.x_) ? T{} : x_ - rhs.x_;
        y_ = cmp::are_equal (y_, rhs.y_) ? T{} : y_ - rhs.y_;
        z_ = cmp::are_equal (z_, rhs.z_) ? T{} : z_ - rhs.z_;

        return *this;
    }

    Vector operator- (const Vector &other) const
    {
        Vector diff = *this;
        return (diff -= other);
    }

    Vector &operator*= (T coeff)
    {
        x_ *= coeff;
        y_ *= coeff;
        z_ *= coeff;

        return *this;
    }

    Vector operator- () const { return Vector{-x_, -y_, -z_}; }

    T norm () const { return x_ * x_ + y_ * y_ + z_ * z_; }

    T module () const { return std::sqrt (norm ()); }

    Vector &normalize ()
    {
        *this *= (1 / module ());

        return *this;
    }

    Vector normalize () const
    {
        Vector tmp = *this;
        tmp.normalize ();

        return tmp;
    }

    bool is_zero () const
    {
        return (cmp::is_zero (x_) && cmp::is_zero (y_) && cmp::is_zero (z_));
    }
};

template<typename T>
Vector<T> operator* (const Vector<T> &vec, T coeff)
{
    auto product = vec;
    return (product *= coeff);
}

template<typename T>
Vector<T> operator* (T coeff, const Vector<T> &vec) { return vec * coeff; }

// Products

template<typename T>
T scalar_product (const Vector<T> &lhs, const Vector<T> &rhs)
{
    auto xx = lhs.x_ * rhs.x_;
    auto yy = lhs.y_ * rhs.y_;
    auto zz = lhs.z_ * rhs.z_;

    auto tmp_product = cmp::are_equal (xx, -yy) ? T{} : xx + yy;
    auto product     = cmp::are_equal (tmp_product, -zz) ? T{} : tmp_product + zz;

    return product;
}

template<typename T>
Vector<T> vector_product (const Vector<T> &lhs, const Vector<T> &rhs)
{
    auto ly_rz     = lhs.y_ * rhs.z_;
    auto lz_ry     = lhs.z_ * rhs.y_;
    auto product_1 = cmp::are_equal (ly_rz, lz_ry) ? T{} : ly_rz - lz_ry;

    auto lz_rx     = lhs.z_ * rhs.x_;
    auto lx_rz     = lhs.x_ * rhs.z_;
    auto product_2 = cmp::are_equal (lz_rx, lx_rz) ? T{} : lz_rx - lx_rz;

    auto lx_ry     = lhs.x_ * rhs.y_;
    auto ly_rx     = lhs.y_ * rhs.x_;
    auto product_3 = cmp::are_equal (lx_ry, ly_rx) ? T{} : lx_ry - ly_rx;

    return Vector<T>{product_1, product_2, product_3};
}

template<typename T>
T triple_product (const Vector<T> &first, const Vector<T> &second, const Vector<T> &third)
{
    return scalar_product (first, vector_product (second, third));
}

// Mutual orientation

template<typename T>
bool are_collinear (const Vector<T> &first, const Vector<T> &second)
{
    return vector_product (first, second).is_zero ();
}

template<typename T>
bool are_parallel (const Vector<T> &first, const Vector<T> &second)
{
    auto sp = scalar_product (first, second);
    return cmp::are_equal (sp, first.module() * second.module());
}

template<typename T>
bool are_antiparallel (const Vector<T> &first, const Vector<T> &second)
{
    auto sp = scalar_product (first, second);
    return cmp::are_equal (-sp, first.module() * second.module());
}

template<typename T>
bool are_coplanar (const Vector<T> &first, const Vector<T> &second, const Vector<T> &third)
{
    return cmp::is_zero (triple_product (first, second, third));
}

template<typename T>
bool are_orthogonal (const Vector<T> &first, const Vector<T> &second)
{
    return cmp::is_zero (scalar_product (first, second));
}

// Printing

template<typename T>
void dump (std::ostream &os, Vector<T> &vec)
{
    os << "(" << vec.x_ << ", " << vec.y_ << ", " << vec.z_ << ")";
}

template<typename T>
std::ostream &operator<< (std::ostream &os, Vector<T> &vec)
{
    dump (os, vec);
    return os;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_VECTOR_HPP
