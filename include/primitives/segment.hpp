#ifndef INCLUDE_PRIMITIVES_SEGMENT_HPP
#define INCLUDE_PRIMITIVES_SEGMENT_HPP

#include <utility>
#include <ostream>
#include <stdexcept>
#include <memory>

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

template<typename T>
class Segment final
{
public:

    using point_type = T;
    using iterator = point_type *;
    using const_iterator = const point_type *;

private:

    point_type points_[2];

public:

    Segment (const point_type &P, const point_type &Q) : points_{P, Q}
    {
        if (is_point ())
            throw Segment_Is_Point{};
    }

    const point_type &P () const { return points_[0]; }
    point_type &P () { return const_cast<point_type &>(static_cast<const Segment &>(*this).P()); }

    const point_type &Q () const { return points_[1]; }
    point_type &Q () { return const_cast<point_type &>(static_cast<const Segment &>(*this).Q()); }

    void swap_points () { std::swap (P(), Q()); }

    iterator begin () { return std::addressof (P()); }
    const_iterator begin () const { return std::addressof (P()); }
    const_iterator cbegin () const { return std::addressof (P()); }

    iterator end () { return std::addressof (points_[2]); }
    const_iterator end () const { return std::addressof (points_[2]); }
    const_iterator cend () const { return std::addressof (points_[2]); }

private:

    bool is_point () const { return P() == Q(); }
};

template<typename T>
bool operator== (const Segment<T> &lhs, const Segment<T> &rhs)
{
    return (lhs.P() == rhs.P() && lhs.Q() == rhs.Q());
}

template<typename T>
void dump (std::ostream &os, const Segment<T> &seg)
{
    os << "P = " << seg.P() << "; "
       << "Q = " << seg.Q();
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const Segment<T> &seg)
{
    dump (os, seg);
    return os;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_SEGMENT_HPP
