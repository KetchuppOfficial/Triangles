#ifndef INCLUDE_TRIANGLE_HPP
#define INCLUDE_TRIANGLE_HPP

#include "point.hpp"
#include "vector.hpp"

#include <algorithm> // for std::swap

namespace Geom_Objects
{

enum TR_TYPE {
    TRIANGLE,
    SEGMENT,
    POINT,
};


struct Triangle
{
    Point P_, Q_, R_;

    Triangle (const Point &P, const Point &Q, const Point &R) : P_ {P}, Q_ {Q}, R_ {R} {}

    bool operator== (const Triangle &rhs) const
    {
        return (P_ == rhs.P_ && Q_ == rhs.Q_ && R_ == rhs.R_);
    }

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

    bool is_point () const { return (P_ == Q_ && Q_ == R_); }

    bool is_segment () const
    {
        Vector PQ {P_, Q_};
        Vector PR {P_, R_};
        
        return are_collinear (PQ, PR);
    }

    TR_TYPE type() const
    {
        if (is_point())
            return TR_TYPE::POINT;
        else if (is_segment())
            return TR_TYPE::SEGMENT;
        else
            return TR_TYPE::TRIANGLE;
    }

};

inline bool point_belong_triangle(const Point& point_A, const Triangle& tr)
{
    Vector PA {tr.P_, point_A};

    Vector PR {tr.P_, tr.R_};
    Vector PQ {tr.P_, tr.Q_};
    Vector QR {tr.Q_, tr.R_};
    if (!are_coplanar(PA, PR, PQ))
        return false;
    
    Vector plane_normal {vector_product(PQ, PR)};
    
    Vector side_PQ_normal {vector_product(PQ, plane_normal)};
    Vector side_PR_normal {vector_product(plane_normal, PR)};
    Vector side_QR_normal {vector_product(QR, plane_normal)};

    Vector RA {tr.R_, point_A};

    if ((scalar_product(vector_product(PQ, plane_normal), PA) <= 0.0) &&
        (scalar_product(vector_product(plane_normal, PR), PA) <= 0.0) &&
        (scalar_product(vector_product(QR, plane_normal), RA) <= 0.0))
        return true; 
    
    return false;
}

inline bool seg_tr_intersecting_2D(const Segment& seg, const Triangle& tr)
{
    if (point_belong_triangle(seg.F(), tr) || point_belong_triangle(seg.S(), tr))
        return true;

    Vector PQ {tr.P_, tr.Q_}, QR {tr.Q_, tr.R_}, RP {tr.R_, tr.P_};
    
    Vector plane_normal {vector_product(RP, PQ)};

    Vector side_PQ_normal {vector_product(PQ, plane_normal)};
    Vector side_QR_normal {vector_product(QR, plane_normal)};
    Vector side_RP_normal {vector_product(RP, plane_normal)};

    Vector FP {seg.F(), tr.P_}, FQ {seg.F(), tr.Q_}, FR {seg.F(), tr.R_};

    bool F_inside_PQ = (scalar_product(FP, side_PQ_normal) >= 0.0);
    bool F_inside_QR = (scalar_product(FQ, side_QR_normal) >= 0.0);
    bool F_inside_RP = (scalar_product(FR, side_RP_normal) >= 0.0);

    bool S_inside_PQ = (scalar_product(Vector {seg.S(), tr.P_}, side_PQ_normal) >= 0.0);
    bool S_inside_QR = (scalar_product(Vector {seg.S(), tr.Q_}, side_QR_normal) >= 0.0);
    bool S_inside_RP = (scalar_product(Vector {seg.S(), tr.R_}, side_RP_normal) >= 0.0);

    enum LOC {
        OUT_ALL             = 000b,
        OUT_PQ_QR_INSIDE_RP = 001b,
        OUT_RP_PQ_INSIDE_QR = 010b,
        OUT_PQ_INSIDE_QR_RP = 011b,
        OUT_QR_RP_INSIDE_PQ = 100b,
        OUT_QR_INSIDE_PQ_RP = 101b,
        OUT_RP_INSIDE_QR_PQ = 110b,
        INSIDE_ALL          = 111b
    }; 
    LOC F_loc = static_cast<LOC>(4 * F_inside_PQ + 2 * F_inside_QR + F_inside_RP);
    LOC S_loc = static_cast<LOC>(4 * S_inside_PQ + 2 * S_inside_QR + S_inside_RP);

    if (F_loc == S_loc)
        return false;

    switch (loc)
    {
        case LOC::OUT_PQ_INSIDE_QR_RP: case LOC::OUT_QR_RP_INSIDE_PQ:
            if (scalar_product(vector_product(seg.FS(), FP), vector_product(seg.FS(), FQ)) <= 0.0)
                return true;
            break;
        case LOC::OUT_RP_INSIDE_QR_PQ: case LOC::OUT_PQ_QR_INSIDE_RP:
            if (scalar_product(vector_product(seg.FS(), FR), vector_product(seg.FS(), FP)) <= 0.0)
                return true;
            break;
        case LOC::OUT_QR_INSIDE_PQ_RP: LOC::OUT_RP_PQ_INSIDE_QR:
            if (scalar_product(vector_product(seg.FS(), FQ), vector_product(seg.FS(), FR)) <= 0.0)
                return true;
            break;
        case LOC::INSIDE_ALL: case LOC::OUT_ALL:
            throw std::logic_error{"Bad cases in switch in seg_tr_intersecting_2d()"};
            break;
        default:
            throw std::logic_error{"Default case in switch in seg_tr_intersecting_2D"};
            break;
    }
    return false;
}

inline bool are_intersecting(const Segment& seg, const Triangle& tr)
{
    auto F_loc = magic_product(tr.P_, tr.Q_, tr.R_, seg.F());
    auto S_loc = magic_product(tr.P_, tr.Q_, tr.R_, seg.S());

    if (F_loc != Loc_3D::On && S_loc != Loc_3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Loc_3D::On && S_loc == Loc_3D::On)
        return seg_tr_intersecting_2D(seg, tr);
    else
        return seg_tr_intersecting_3D(seg, tr);
}

} // namespace Geom_Objects

#endif // INCLUDE_TRIANGLE_HPP
