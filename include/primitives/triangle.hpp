#ifndef INCLUDE_PRIMITIVES_TRIANGLE_HPP
#define INCLUDE_PRIMITIVES_TRIANGLE_HPP

#include <algorithm>
#include <ostream>

#include "point.hpp"
#include "vector.hpp"

namespace yLab
{

namespace geometry
{

enum class Tr_Species
{
    point = -1,
    segment = 0,
    triangle = 1
};

template<typename Point_T> class Triangle final
{
    Point_T P_, Q_, R_;
    Tr_Species type_ = Tr_Species::triangle;

public:

    Triangle (const Point_T &P, const Point_T &Q, const Point_T &R)
             : P_{P}, Q_{Q}, R_{R}
    {
        if (is_point (*this))
            type_ = Tr_Species::point;
        else if (is_segment (*this))
            type_ = Tr_Species::segment;
    }

    const Point_T &P () const { return P_; }
    const Point_T &Q () const { return Q_; }
    const Point_T &R () const { return R_; }

    Tr_Species type () const { return type_; }

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

template<typename Point_T>
bool operator== (const Triangle<Point_T> &lhs, const Triangle<Point_T> &rhs)
{
    return (lhs.P() == rhs.P() && lhs.Q() == rhs.Q() && lhs.R() == rhs.R());  
}

template<typename Point_T>
bool is_point (const Triangle<Point_T> &tr) { return (tr.P() == tr.Q() && tr.Q() == tr.R()); }

template<typename Point_T>
bool is_segment (const Triangle<Point_T> &tr)
{
    Vector PQ{tr.P(), tr.Q()};
    Vector PR{tr.P(), tr.R()};
    
    return are_collinear (PQ, PR);
}

template<typename Point_T>
void dump (std::ostream &os, const Triangle<Point_T> &tr)
{
    os << "P = " << tr.P() << "; "
       << "Q = " << tr.Q() << "; "
       << "R = " << tr.R();
}

template<typename Point_T>
std::ostream &operator<< (std::ostream &os, const Triangle<Point_T> &tr)
{
    dump (os, tr);
    return os;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_TRIANGLE_HPP
