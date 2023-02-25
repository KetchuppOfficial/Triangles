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

template<typename Point_T> class Triangle final
{
    Point_T P_, Q_, R_;

public:

    Triangle (const Point_T &P, const Point_T &Q, const Point_T &R)
             : P_{P}, Q_{Q}, R_{R}
    {
        if (is_point ())
            throw Triangle_Is_Point{};
        else if (is_segment ())
            throw Triangle_Is_Segment{};
    }

    const Point_T &P () const { return P_; }
    const Point_T &Q () const { return Q_; }
    const Point_T &R () const { return R_; }

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

private:

    bool is_point () const { return (P_ == Q_ && Q_ == R_); }

    bool is_segment () const
    {
        Vector PQ{P_, Q_};
        Vector PR{P_, R_};
        
        return are_collinear (PQ, PR);
    }
};

template<typename Point_T>
bool operator== (const Triangle<Point_T> &lhs, const Triangle<Point_T> &rhs)
{
    return (lhs.P() == rhs.P() && lhs.Q() == rhs.Q() && lhs.R() == rhs.R());  
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
