#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "plane.hpp"
#include "triangle.hpp"
#include <iostream>

namespace Geom_Objects
{

class Segment {
    Point F_, S_;
    Vector FS_;

    public:
    Segment(const Point& f, const Point& s): F_ {f}, S_ {s}, FS_ {Vector {F_, S_}}
    {
        #ifndef RELEASE
        if (F_ == S_)
            throw std::invalid_argument{"try to create segment from equal dots"};
        #endif
    }

    Segment(const Triangle& tr)
    {
        Vector PQ {tr.P(), tr.Q()};
        Vector RQ {tr.R(), tr.Q()};

        if (scalar_product(PQ, RQ) <= 0.0)
        {
            F_ = tr.P();
            S_ = tr.R();
        }
        else
        {
            F_ = tr.Q();
            if (PQ.norm() > RQ.norm())
                S_ = tr.P();
            else
                S_ = tr.R();
        }
        FS_ = Vector {F_, S_};
    }

    const Point& F() const noexcept {return F_;}
    const Point& S() const noexcept {return S_;}
    const Vector& FS() const noexcept {return FS_;}

    void swap_points() noexcept
    {
        std::swap(F_, S_);
        FS_ = -FS_;
    }
};

inline bool point_belong_segment(const Point& point, const Segment& segment)
{
    Vector PF {point, segment.F()};
    Vector PS {point, segment.S()};

    if (!are_collinear(PF, PS))
        return false;
    else if (scalar_product(PF, segment.FS()) * scalar_product(PS, segment.FS()) <= 0.0)
        return true;
    else
        return false;
}

enum Loc_2D_LH
{
    Out = -1,
    On  = 0,
    In  = 1
};

inline Loc_2D_LH magic_product_2D_LH(const Point& A, const Point& B, const Point& C, const Vector& plane_normal)
{
    double prod = triple_product(Vector {A, B}, Vector {A, C}, plane_normal);

    if (cmp::are_equal(prod, 0.0))
        return Loc_2D_LH::On;
    else if (prod > 0.0)
        return Loc_2D_LH::In;
    else
        return Loc_2D_LH::Out;  
}

inline bool point_belong_triangle(const Point& point_A, const Triangle& tr)
{
    if (magic_product(tr.P(), tr.Q(), tr.R(), point_A) != Loc_3D::On)
        return false;

    Vector plane_normal {tr.make_plane_normal()};
    
    if (magic_product_2D_LH(tr.P(), tr.Q(), point_A, plane_normal) != Loc_2D_LH::Out &&
        magic_product_2D_LH(tr.Q(), tr.R(), point_A, plane_normal) != Loc_2D_LH::Out &&
        magic_product_2D_LH(tr.R(), tr.P(), point_A, plane_normal) != Loc_2D_LH::Out)
        return true;
    
    std::cout << "ALARM!!!" << std::endl << std::endl;
    return false;
}


inline bool are_intersecting(const Segment& seg1, const Segment& seg2)
{
    Line line1 {seg1.F(), seg1.FS()}, line2 {seg2.F(), seg2.FS()};
    if (!are_intersecting(line1, line2))
        return false;

    if (line1 == line2)
    {
        Line& line = line1;
        Segment seg2_cpy {seg2};

        const Point& A1 = seg1.F();
        const Point& B1 = seg1.S();
        if (scalar_product(seg1.FS(), seg2_cpy.FS()) < 0.0)
            seg2_cpy.swap_points();
        const Point& A2 = seg2_cpy.F();
        const Point& B2 = seg2_cpy.S();

        Vector B1A2 {B1, A2};
        Vector B2A1 {B2, A1};

        if (scalar_product(B1A2, line.drc_vec()) >= 0.0 || scalar_product(B2A1, line.drc_vec()) >= 0.0)
            return false;
        return true;  
    }

    Vector plane_normal {vector_product(seg1.FS(), seg2.FS())};

    if ((magic_product_2D_LH(seg1.F(), seg1.S(), seg2.F(), plane_normal) * magic_product_2D_LH(seg1.F(), seg1.S(), seg2.S(), plane_normal) <= 0) &&
        (magic_product_2D_LH(seg2.F(), seg2.S(), seg1.F(), plane_normal) * magic_product_2D_LH(seg2.F(), seg2.S(), seg1.S(), plane_normal) <= 0))
        return true;
    return false;
}

inline bool seg_tr_intersecting_2D(const Segment& seg, const Triangle& tr)
{
    if (point_belong_triangle(seg.F(), tr) || point_belong_triangle(seg.S(), tr))
        return true;

    if (are_intersecting(seg, Segment {tr.P(), tr.Q()}) ||
        are_intersecting(seg, Segment {tr.Q(), tr.R()}) ||
        are_intersecting(seg, Segment {tr.R(), tr.P()}))
        return true;

    return false;
}

inline bool alt_seg_tr_intersecting_2D(const Segment& seg, const Triangle& tr)
{
    if (point_belong_triangle(seg.F(), tr) || point_belong_triangle(seg.S(), tr))
        return true;

    const Point& F = seg.F();
    const Point& S = seg.S();
    
    Vector plane_normal {tr.make_plane_normal()};

    Vector FP {F, tr.P()}, FQ {F, tr.Q()}, FR {F, tr.R()};

    bool F_inside_PQ = (magic_product_2D_LH(tr.P(), tr.Q(), F, plane_normal) != Loc_2D_LH::In);
    bool F_inside_QR = (magic_product_2D_LH(tr.Q(), tr.R(), F, plane_normal) != Loc_2D_LH::In);
    bool F_inside_RP = (magic_product_2D_LH(tr.R(), tr.P(), F, plane_normal) != Loc_2D_LH::In);

    bool S_inside_PQ = (magic_product_2D_LH(tr.P(), tr.Q(), S, plane_normal) != Loc_2D_LH::In);
    bool S_inside_QR = (magic_product_2D_LH(tr.Q(), tr.R(), S, plane_normal) != Loc_2D_LH::In);
    bool S_inside_RP = (magic_product_2D_LH(tr.R(), tr.P(), S, plane_normal) != Loc_2D_LH::In);

    enum LOC {
        OUT_ALL             = 0b000,
        OUT_PQ_QR_INSIDE_RP = 0b001,
        OUT_RP_PQ_INSIDE_QR = 0b010,
        OUT_PQ_INSIDE_QR_RP = 0b011,
        OUT_QR_RP_INSIDE_PQ = 0b100,
        OUT_QR_INSIDE_PQ_RP = 0b101,
        OUT_RP_INSIDE_QR_PQ = 0b110,
        INSIDE_ALL          = 0b111
    }; 
    LOC F_loc = static_cast<LOC>(4 * F_inside_PQ + 2 * F_inside_QR + F_inside_RP);
    LOC S_loc = static_cast<LOC>(4 * S_inside_PQ + 2 * S_inside_QR + S_inside_RP);

    if (F_loc == S_loc)
        return false;

    switch (F_loc)
    {
        case LOC::OUT_PQ_INSIDE_QR_RP: case LOC::OUT_QR_RP_INSIDE_PQ:
            if (scalar_product(vector_product(seg.FS(), FP), vector_product(seg.FS(), FQ)) <= 0.0)
                return true;
            break;
        case LOC::OUT_RP_INSIDE_QR_PQ: case LOC::OUT_PQ_QR_INSIDE_RP:
            if (scalar_product(vector_product(seg.FS(), FR), vector_product(seg.FS(), FP)) <= 0.0)
                return true;
            break;
        case LOC::OUT_QR_INSIDE_PQ_RP: case LOC::OUT_RP_PQ_INSIDE_QR:
            if (scalar_product(vector_product(seg.FS(), FQ), vector_product(seg.FS(), FR)) <= 0.0)
                return true;
            break;
        case LOC::INSIDE_ALL: case LOC::OUT_ALL:
            throw std::logic_error{"Bad cases in switch in seg_tr_intersecting_2D()"};
            break;
        default:
            throw std::logic_error{"Default case in switch in seg_tr_intersecting_2D()"};
            break;
    }
    return false;
}

inline bool seg_tr_intersecting_3D(const Segment& seg, const Triangle& tr)
{
    const Point& P = tr.P(), Q = tr.Q(), R = tr.R(), F = seg.F(), S = seg.S();

    if (point_belong_segment(P, seg) ||
        point_belong_segment(Q, seg) ||
        point_belong_segment(R, seg))
        return true;

    if (magic_product(P, F, S, Q) != magic_product(P, F, S, R) &&
        magic_product(Q, F, S, P) != magic_product(Q, F, S, R) &&
        magic_product(R, F, S, P) != magic_product(R, F, S, Q))
        return true;
    return false;
}

inline bool segment_and_triangle_intersecting(const Segment& seg, const Triangle& tr)
{
    auto F_loc = magic_product(tr.P(), tr.Q(), tr.R(), seg.F());
    auto S_loc = magic_product(tr.P(), tr.Q(), tr.R(), seg.S());

    if (F_loc != Loc_3D::On && S_loc != Loc_3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Loc_3D::On && S_loc == Loc_3D::On)
        return seg_tr_intersecting_2D(seg, tr);
    else
        return seg_tr_intersecting_3D(seg, tr);
}

}