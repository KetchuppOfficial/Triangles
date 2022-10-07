#pragma once
#include "double_comparison.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace Geom_Objects
{

class Line
{
    Vector drc_vec_;

public:

    Point point_;
    Line (const Point &p1, const Point &p2)
        : point_ {p1}, drc_vec_ {p1.x_ - p2.x_, p1.y_ - p2.y_, p1.z_ - p2.z_}
    {
#ifndef RELEASE
        if (p1 == p2)
            throw std::invalid_argument {"In constructor of Line(Point, Point): two equal points"};
#endif
    }

    Line (const Point &p, const Vector &vec) : point_ {p}, drc_vec_ {vec}
    {
#ifndef RELEASE
        if (vec.is_zero ())
            throw std::invalid_argument {"In constructor of Line(Point, Vector): null vector"};
#endif
    }

    const Vector &drc_vec () const { return drc_vec_; }

    const Vector &drc_vec (const Vector &new_vec)
    {
#ifndef RELEASE
        if (new_vec.is_zero ())
            throw std::invalid_argument {"In method of change drc_vec(): null vector"};
#endif
        drc_vec_ = new_vec;
        return drc_vec_;
    }

    bool operator== (const Line &other) const
    {
        if (point_ == other.point_)
            return are_collinear (drc_vec_, other.drc_vec_);
        return are_collinear (Vector {point_, other.point_}, drc_vec_);
    }

    bool operator!= (const Line &other) const { return !(*this == other); }
};

bool are_parallel (const Line &line1, const Line &line2)
{
    return are_collinear (line1.drc_vec (), line2.drc_vec ());
}

double distance (const Line &line, const Point &pt)
{
    Vector dot_vec {pt, line.point_};
    double coef = scalar_product (dot_vec, line.drc_vec ()) /
                  scalar_product (line.drc_vec (), line.drc_vec ());
    return (dot_vec - coef * line.drc_vec ()).module ();
}

double distance (const Point &pt, const Line &line) { return distance (line, pt); }

double distance (const Line &line1, const Line &line2)
{
    if (are_parallel (line1, line2))
        return vector_product ({line1.point_, line2.point_}, line1.drc_vec ()).module () /
               line1.drc_vec ().module ();

    Vector dots_vec {line1.point_, line2.point_};
    return triple_product (dots_vec, line1.drc_vec (), line2.drc_vec ().module ()) /
           vector_product (line1.drc_vec (), line2.drc_vec ()).module ();
}

bool are_intersect (const Line &line1, const Line &line2)
{
    return Comparison::are_equal (distance (line1, line2), 0);
}

bool is_belong (const Point &pt, const Line &line)
{
    return Comparison::are_equal (distance (pt, line), 0);
}
bool is_belong (const Line &line, const Point &pt) { return is_belong (pt, line); }

bool in_plane (const Line &line1, const Line &line2)
{
    if (are_parallel (line1, line2))
        return true;
    return are_intersect (line1, line2);
}
bool is_belong (const Line &line, const Point &pt) { return is_belong (pt, line); }

} // namespace Geom_Objects