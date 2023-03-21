#ifndef INCLUDE_PRIMITIVES_TRIANGLE_HPP
#define INCLUDE_PRIMITIVES_TRIANGLE_HPP

#include <algorithm>
#include <ostream>
#include <exception>

#include "point.hpp"
#include "vector.hpp"

namespace yLab
{

namespace geometry
{

struct Degenerate_Triangle : public std::runtime_error
{
    Degenerate_Triangle (const char *message) : std::runtime_error{message} {}
};

struct Triangle_Is_Point : public Degenerate_Triangle
{
    Triangle_Is_Point () : Degenerate_Triangle{"The triangle has degenerate into a point"} {} 
};

struct Triangle_Is_Segment : public Degenerate_Triangle
{
    Triangle_Is_Segment () : Degenerate_Triangle{"The triangle has degenerate into a segment"} {} 
};

template<typename T> class Triangle final
{
public:

    using point_type = T;
    using distance_type = typename point_type::distance_type;
    using iterator = point_type *;
    using const_iterator = const point_type *;

private:
    
    point_type points_[3];

public:

    Triangle (const point_type &P, const point_type &Q, const point_type &R) : points_{P, Q, R}
    {
        if (is_point ())
            throw Triangle_Is_Point{};
        else if (is_segment ())
            throw Triangle_Is_Segment{};
    }

    const point_type &P () const { return points_[0]; }
    point_type &P () { return const_cast<point_type &>(static_cast<const Triangle &>(*this).P()); }

    const point_type &Q () const { return points_[1]; }
    point_type &Q () { return const_cast<point_type &>(static_cast<const Triangle &>(*this).Q()); }

    const point_type &R () const { return points_[2]; }
    point_type &R () { return const_cast<point_type &>(static_cast<const Triangle &>(*this).R()); }

    void swap_QR () { std::swap (Q(), R()); }

    void swap_clockwise ()
    {
        std::swap (P(), R());
        std::swap (Q(), R());
    }

    void swap_counterclockwise ()
    {
        std::swap (P(), Q());
        std::swap (R(), Q());
    }

    Vector<distance_type> norm () const
    {
        return vector_product (Vector{P(), Q()}, Vector{P(), R()});
    }

    iterator begin () { return std::addressof (P()); }
    const_iterator begin () const { return std::addressof (P()); }
    const_iterator cbegin () const { return begin(); }

    iterator end () { return std::addressof (points_[3]); }
    const_iterator end () const { return std::addressof(points_[3]); }
    const_iterator cend () const { return end(); }

private:

    bool is_point () const { return (P() == Q() && Q() == R()); }

    bool is_segment () const
    {
        Vector PQ{P(), Q()};
        Vector PR{P(), R()};
        
        return are_collinear (PQ, PR);
    }
};

template<typename T>
bool operator== (const Triangle<T> &lhs, const Triangle<T> &rhs)
{
    return (lhs.P() == rhs.P() && lhs.Q() == rhs.Q() && lhs.R() == rhs.R());  
}

template<typename T>
void dump (std::ostream &os, const Triangle<T> &tr)
{
    os << "P = " << tr.P() << "; "
       << "Q = " << tr.Q() << "; "
       << "R = " << tr.R();
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const Triangle<T> &tr)
{
    dump (os, tr);
    return os;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_TRIANGLE_HPP
