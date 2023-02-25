#ifndef INCLUDE_PRIMITIVES_SEGMENT_HPP
#define INCLUDE_PRIMITIVES_SEGMENT_HPP

#include <type_traits>
#include <utility>

#include "point.hpp"

namespace yLab
{

namespace geometry
{

template<typename Point_T>
class Segment final
{
    Point_T P_, Q_;

public:

    Segment (const Point_T &P, const Point_T &Q) : P_{P}, Q_{Q} {}

    const Point_T &P () const { return P_; }
    const Point_T &Q () const { return Q_; }

    void swap_points () { std::swap (P_, Q_); }
};

template<typename Point_T>
bool operator== (const Segment<Point_T> &lhs, const Segment<Point_T> &rhs)
{
    return (lhs.P() == rhs.P() && lhs.Q() == rhs.Q());
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_SEGMENT_HPP
