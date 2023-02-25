#ifndef INCLUDE_PRIMITIVES_SEGMENT_HPP
#define INCLUDE_PRIMITIVES_SEGMENT_HPP

#include <utility>
#include <ostream>
#include <exception>

#include "point.hpp"

namespace yLab
{

namespace geometry
{

struct Degenerate_Segment : public std::runtime_error
{
    Degenerate_Segment (const char *message) : std::runtime_error{message} {}
};

struct Segment_Is_Point : public Degenerate_Segment
{
    Segment_Is_Point () : Degenerate_Segment{"The segment has degenerate into a point"} {} 
};

template<typename Point_T>
class Segment final
{
    Point_T P_, Q_;

public:

    Segment (const Point_T &P, const Point_T &Q) : P_{P}, Q_{Q}
    {
        if (is_point ())
            throw Segment_Is_Point{};
    }

    const Point_T &P () const { return P_; }
    const Point_T &Q () const { return Q_; }

    void swap_points () { std::swap (P_, Q_); }

private:

    bool is_point () const { return P_ == Q_; }
};

template<typename Point_T>
bool operator== (const Segment<Point_T> &lhs, const Segment<Point_T> &rhs)
{
    return (lhs.P() == rhs.P() && lhs.Q() == rhs.Q());
}

template<typename Point_T>
void dump (std::ostream &os, const Segment<Point_T> &seg)
{
    os << "P = " << seg.P() << "; "
       << "Q = " << seg.Q();
}

template<typename Point_T>
std::ostream &operator<< (std::ostream &os, const Segment<Point_T> &seg)
{
    dump (os, seg);
    return os;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_SEGMENT_HPP
