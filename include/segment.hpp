#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "plane.hpp"
#include "triangle.hpp"
#include <iostream>

namespace Geom_Objects
{

struct Segment {
    Point F_, S_;
    
    Segment(const Point& F, const Point& S): F_ {F}, S_ {S}
    {
        #ifndef RELEASE
        if (F_ == S_)
            throw std::invalid_argument{"try to create segment from equal dots"};
        #endif
    }

    Segment(const Triangle& tr)
    {
        #ifndef RELEASE
        if (tr.type() != Tr_Type::Segment_)
            throw std::logic_error{"In ctor Segmnet by Triangle type of Triangle isnt Segemnt_"};
        #endif

        Vector PQ {tr.P(), tr.Q()};
        Vector RQ {tr.R(), tr.Q()};

        if (scalar_product(PQ, RQ) < 0.0 || tr.P() == tr.R())
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
    }

    void swap_points() noexcept
    {
        std::swap(F_, S_);
    }
};

inline bool point_belong_segment(const Point& point, const Segment& segment)
{
    Vector PF {point, segment.F_};
    Vector PS {point, segment.S_};

    if (!are_collinear(PF, PS))
        return false;
    else if (scalar_product(PF,PS) < 0.0 || segment.F_ == point || segment.S_ == point)
        return true;
    else
        return false;
}

enum Loc_Points {
    In_Same = 1,
    In_Different = -1,
    On_Line = 0,
};

inline Loc_Points laying_in_same_half(const Point& A, const Point& B, const Point& C, const Point& D)
{
    Vector AB {A, B}, AC {A, C}, AD {A, D};

    auto prod = scalar_product(vector_product(AB, AC), vector_product(AB, AD));

    if (cmp::are_equal(prod, 0.0))
        return Loc_Points::On_Line;
    else if (prod > 0.0)
        return  Loc_Points::In_Same;
    else
        return Loc_Points::In_Different;
}

inline bool point_belong_triangle(const Point& point_A, const Triangle& tr)
{
    if (magic_product(tr.P(), tr.Q(), tr.R(), point_A) != Loc_3D::On)
        return false;
    
    return laying_in_same_half(tr.P(), tr.Q(), tr.R(), point_A) != Loc_Points::In_Different &&
           laying_in_same_half(tr.Q(), tr.R(), tr.P(), point_A) != Loc_Points::In_Different &&
           laying_in_same_half(tr.R(), tr.P(), tr.Q(), point_A) != Loc_Points::In_Different;
}

inline bool are_intersecting(const Segment& seg1, const Segment& seg2)
{
    Vector F1S1 {seg1.F_, seg1.S_};
    Vector F2S2 {seg2.F_, seg2.S_};
    
    Line line1 {seg1.F_, F1S1}, line2 {seg2.F_, F2S2};
    if (!are_intersecting(line1, line2))
        return false;

    if (line1 == line2)
    {
        Segment seg2_cpy {seg2};

        const Point& A1 = seg1.F_;
        const Point& B1 = seg1.S_;
        if (scalar_product(F1S1, F2S2) < 0.0)
            seg2_cpy.swap_points();
        const Point& A2 = seg2_cpy.F_;
        const Point& B2 = seg2_cpy.S_;

        Vector B1A2 {B1, A2};
        Vector B2A1 {B2, A1};

        auto prod_B1A2_B2A1 = scalar_product(B1A2, B2A1);

        return prod_B1A2_B2A1 > 0.0 || cmp::are_equal(prod_B1A2_B2A1, 0.0); 
    }

    return laying_in_same_half(seg1.F_, seg1.S_, seg2.F_, seg2.S_) != Loc_Points::In_Same &&
           laying_in_same_half(seg2.F_, seg2.S_, seg1.F_, seg1.S_) != Loc_Points::In_Same;
}

inline bool seg_tr_intersecting_2D(const Segment& seg, const Triangle& tr)
{
    if (point_belong_triangle(seg.F_, tr) || point_belong_triangle(seg.S_, tr))
        return true;

    return are_intersecting(seg, Segment {tr.P(), tr.Q()}) ||
           are_intersecting(seg, Segment {tr.Q(), tr.R()}) ||
           are_intersecting(seg, Segment {tr.R(), tr.P()});
}

/*
inline bool alt_seg_tr_intersecting_2D(const Segment& seg, const Triangle& tr)
{
    if (point_belong_triangle(seg.F_, tr) || point_belong_triangle(seg.S_, tr))
        return true;

    const Point& F = seg.F_;
    const Point& S = seg.S_;
    
    Vector plane_normal {tr.normal()};

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
*/

inline bool seg_tr_intersecting_3D(const Segment& seg, const Triangle& tr)
{
    const Point& P = tr.P(), Q = tr.Q(), R = tr.R(), F = seg.F_, S = seg.S_;

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
    auto F_loc = magic_product(tr.P(), tr.Q(), tr.R(), seg.F_);
    auto S_loc = magic_product(tr.P(), tr.Q(), tr.R(), seg.S_);

    if (F_loc != Loc_3D::On && S_loc != Loc_3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Loc_3D::On && S_loc == Loc_3D::On)
        return seg_tr_intersecting_2D(seg, tr);
    else
        return seg_tr_intersecting_3D(seg, tr);
}

} //namespace Geom_Obj