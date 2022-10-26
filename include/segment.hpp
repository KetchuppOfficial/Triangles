#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "triangle.hpp"

namespace Geom_Objects{

struct Segment {
    Point F;
    Point S;
    Vector FS;
    Segment(const Point& f, const Point& s): F {f}, S {s}, FS {Vector {F, S}} {}
    Segment(const Triangle& tr)
    {
        Vector PQ {tr.P_, tr.Q_};
        Vector RQ {tr.R_, tr.Q_};
        
        if (directionals(PQ, RQ) == DRC::OPPOSITE_DRC)
        {
            F = tr.P_;
            S = tr.R_;
        }
        else
        {
            F = tr.Q_;
            if (PQ.norm() > RQ.norm())
                S = tr.P_;
            else
                S = tr.R_;
        }

        FS = Vector {F, S};
    }
};

inline bool point_belong_segment(const Point& point, const Segment& segment)
{
    if (directionals(Vector {point, segment.F}, Vector {point, segment.S}) == DRC::OPPOSITE_DRC)
        return true;
    return false;
}

inline bool are_intersecting(const Segment& seg1, const Segment seg2)
{
    if (!are_intersecting(Line {seg1.F, seg1.S}, Line {seg2.F, seg2.S}))
        return false;
    
    Vector F1S2 {seg1.F, seg2.S};
    Vector F1F2 {seg1.F, seg2.F};

    Vector F2S1 {seg2.F, seg1.S};
    Vector F2F1 {seg2.F, seg1.F};

    if (scalar_product(F1S2, seg2.FS) * scalar_product(F1F2, seg2.FS) <= 0.0 &&
        scalar_product(F2S1, seg1.FS) * scalar_product(F2F1, seg1.FS) <= 0.0)
        return true;
    return false;
}

}