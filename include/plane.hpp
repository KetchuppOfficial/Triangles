#pragma once

#include "double_comparison.hpp"
#include "line.hpp"
#include "point.hpp"
#include "vector.hpp"

#include <stdexcept> //  std::invalid_argument

namespace Geom_Objects
{

class Plane
{
    //  By an origin and normal vector of the plane
    Vector normal_;
    Point origin_;

public:

    Plane () { throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"}; }

    Plane (const Point &origin, const Vector &normal)
    {
        if (normal.is_zero ())
            throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"};
        normal_ = normal * (1 / normal.module ());
        origin_ = origin;
    }

    //  Bad idea to construct a plane by 4 doubles
    Plane (double A, double B, double C, double D)
    {
        normal_ = {A, B, C};
        //  Three comparisons to not create unnecessery evict as vector
        if (normal_.is_zero ())
            throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"};
        if (cmp::are_equal (A, 0.0))
        {
            if (cmp::are_equal (B, 0.0))
                origin_ = {0, 0, -D / C};
            else
                origin_ = {0, -D / B, 0};
        }
        else
            origin_ = {-D / A, 0, 0};

        normal_ *= (1 / normal_.module ());
    }

    Point origin () const { return Point {origin_.x_, origin_.y_, origin_.z_}; };
    Vector norm_vec () const { return Vector {normal_.x_, normal_.y_, normal_.z_}; };
};

//  block with Plane and Point
double distance (const Point &p, const Plane &pl)
{
    Point origin = pl.origin ();
    Vector diff  = {p.x_ - origin.x_, p.y_ - origin.y_, p.z_ - origin.z_};
    double coef  = scalar_product (diff, pl.norm_vec ());
    diff         = coef * pl.norm_vec ();
    return diff.module ();
}
double distance (const Plane &pl, const Point &p);

bool is_belong (const Point &p, const Plane &pl) { return cmp::are_equal (distance (p, pl), 0.0); }

//  block with Plane and Line
bool is_intersect (const Line &line, const Plane &pl)
{
    return !cmp::are_equal (scalar_product (pl.norm_vec (), line.drc_vec ()), 0.0);
}

bool are_parallel (const Plane &pl, const Line &line) { return !is_intersect (line, pl); }
bool are_parallel (const Line &line, const Plane &pl) { return are_parallel (pl, line); }

bool is_belong (const Line &line, const Plane &pl)
{
    return is_belong (line.point_, pl) && are_parallel (line, pl);
}

double distance (const Plane &pl, const Line &line)
{
    if (is_intersect (line, pl))
        throw std::invalid_argument {"No distance between plane and line intersected it\n"};
    if (is_belong (line, pl))
        return 0.0;
    Vector diff {pl.origin (), line.point_};
    return std::abs (scalar_product (diff, pl.norm_vec ()));
}
double distance (const Line &line, const Plane &pl) { return distance (pl, line); }

//  block with Plane and Plane
bool are_parallel (const Plane &pl1, const Plane &pl2)
{
    return are_collinear (pl1.norm_vec (), pl2.norm_vec ());
}
bool are_intersect (const Plane &pl1, const Plane &pl2) { return !are_parallel (pl1, pl2); }
bool are_equal (const Plane &pl1, const Plane &pl2)
{
    return are_parallel (pl1, pl2) && is_belong (pl1.origin (), pl2);
}

double distance (const Plane &pl1, const Plane &pl2)
{
    if (!are_parallel (pl1, pl2))
        throw std::invalid_argument {"No distance between intersected planes\n"};
    if (are_equal (pl1, pl2))
        return 0.0;
    Vector diff {pl1.origin (), pl2.origin ()};
    return std::abs (scalar_product (pl1.norm_vec (), diff));
}

} //  namespace Geom_Objects
