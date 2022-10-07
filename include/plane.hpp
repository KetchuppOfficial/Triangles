#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "double_comparison.hpp"

namespace Geom_Objects
{

class Plane
{
    //  from general form of plane: Ax + By + Cz + D = 0
    double A_, B_, C_, D_;

public:
    Plane (double A, double B, double C, double D) : A_{A}, B_{B}, C_{C}, D_{D} 
    {
        //  three cmps to not create unnecessery evict as vector
        if (cmp::are_equal (A, 0.0)
        &&  cmp::are_equal (B, 0.0)
        &&  cmp::are_equal (C, 0.0))
            throw std::invalid_argument {"In constructor of Plane(A, B, C, D): zero normal vector\n"};
    }

    Plane (const Point& p, const Vector& rhs) : A_{rhs.x_}, B_{rhs.y_}, C_{rhs.z_}, 
                                                D_{p.x_*rhs.x_ + p.y_*rhs.y_ + p.z_*rhs.z_}
    {
        if (rhs.is_zero())
            throw std::invalid_argument {"In constuctor of Plane(Vector normal, Point origin): zero normal\n"};
    }

    Vector norm_vec () const { return Vector norm = {A_, B_, C_}; };
    Point  origin () const {return Point or = {p.x_*rhs.x_, p.y_*rhs.y_, p.z_*rhs.z_};}

};

//  block with Plane and Point
double distance (const Point& p, const Plane& pl)
{
    Vector vec  = {p.x_ - pl.x_, p.y_ - pl.y_, p.z_ - pl.z_};
    double coef = scalar_product (vec, pl.norm_vec()); 
    Vector prc  = vec * coef;
    return prv.module();
}

double distance (const Plane& pl, const Point& p) { return distance (p, pl); }

bool is_belong (const Point& p, const Plane& pl) { return cmp::are_equal (distance (p, pl), 0.0); }

//  block with Plane and Line
bool is_intersect (const Line& line, const Plane& pl) {
    return cmp::are_equal (scalar_product (pl.norm_vec(), line.drc_vec_),0.0); 
}

bool are_paral (const Plane& pl, const Line& line) { return are_collinear(pl.norm_vec(), line.drc_vec_); }
bool are_paral (const Line& line, const Plane& pl) { return are_paral(pl, line); }

bool is_consisted (const Line& line, const Plane& pl) 
{
    return cmp::are_equal(pl.A_*line.point_.x_ + pl.B_*line.point_.y_ + pl.C_*line.point_.z_ + pl.D_, 0.0) 
        && cmp::are_equal(pl.A_*line.drc_vec_.x_ + pl.B_*line.drc_vec_.y_ + pl.C_*line.drc_vec_.z_, 0.0);
}

Point p_intersect (const Line& line, const Plane& pl)
{
    if (!is_intersect (line, pl))
        return Point p = {nan, nan, nan};
    //  from radius-vector form of line: r = r_{0} + drc_vec_*t
    double t = - (pl.A_*line.point_.x_ + pl.B_*line.point_.y_ + pl.C_*line.point_.z_ + pl.D_) / 
                 (pl.A_*line.drc_vec_.x_ + pl.B_*line.drc_vec_.y_ + pl.C_*line.drc_vec_.z_);
    return Point p_inrs = { line.point_.x_ + line.drc_vec_.x_*t
                          + line.point_.y_ + line.drc_vec_.y_*t
                          + line.point_.z_ + line.drc_vec_.z_*t};
}

double distance (const Plane& pl, const Line& line)
{
    if (is_consisted(pl, line))
        return 0.0;
    return vector_product (pl.norm_vec(), line.drc_vec_).module();
}
double distance (const Line& line, const Plane& pl) { return distance(pl, line); }

//  block with Plane and Plane
bool are_paral (const Plane& pl1, const Plane& pl2) {
    return cmp::are_equal (scalar_product(pl1.norm_vec(), pl2.norm_vec()), 0.0);
}
bool are_intersect (const Plane& pl1, const Plane& pl2) { return !are_paral(pl1, pl2) }\
bool are_equal (const Plane& pl1, const Plane& pl2) { 
    return are_paral(pl1, pl2) && cmp::are_equal (pl1.D_, pl2.D_); 
}

double distance (const Plane& pl1, const Plane& pl2)
{
    if (are_equal(pl1, pl2))
        return 0.0;
    return std::abs(pl1.D_ - pl2.D_); 
}

}   //  namespace Geom_Objects