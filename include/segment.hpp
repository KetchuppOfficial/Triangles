#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "plane.hpp"
#include "triangle.hpp"
#include <iostream>

namespace Geom_Objects{

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
        Vector PQ {tr.P_, tr.Q_};
        Vector RQ {tr.R_, tr.Q_};

        if (scalar_product(PQ, RQ) <= 0.0)
        {
            std::cout << "in if" << std::endl;
            F_ = tr.P_;
            S_ = tr.R_;
        }
        else
        {
            std::cout << "in else" << std::endl;
            F_ = tr.Q_;
            if (PQ.norm() > RQ.norm())
            {
                std::cout << "in else if" << std::endl;
                S_ = tr.P_;
            }
            else
            {
                std::cout << "in else else" << std::endl;
                S_ = tr.R_;
            }
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

    Vector line1_normal {vector_product(plane_normal, seg1.FS())};
    Vector F1F2 {seg1.F(), seg2.F()};
    Vector F1S2 {seg1.F(), seg2.S()};

    if (scalar_product(F1F2, line1_normal) * scalar_product(F1S2, line1_normal) > 0.0)
        return false;
    
    Vector line2_normal {vector_product(plane_normal, seg2.FS())};
    //we already has F1F2 which is opposite to F2F1,
    //and we can just a litle bit change out algorithm
    Vector F2S1 {seg2.F(), seg1.S()};

    if (!(scalar_product(F1F2, line2_normal) * scalar_product(F2S1, line2_normal) < 0.0))
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
            throw std::logic_error{"Bad cases in switch in seg_tr_intersecting_2d()"};
            break;
        default:
            throw std::logic_error{"Default case in switch in seg_tr_intersecting_2D"};
            break;
    }
    return false;
}

/*inline bool are_intersecting(const Segment& seg, const Triangle& tr)
{
    auto F_loc = magic_product(tr.P_, tr.Q_, tr.R_, seg.F());
    auto S_loc = magic_product(tr.P_, tr.Q_, tr.R_, seg.S());

    if (F_loc != Loc_3D::On && S_loc != Loc_3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Loc_3D::On && S_loc == Loc_3D::On)
        return seg_tr_intersecting_2D(seg, tr);
    else
        return seg_tr_intersecting_3D(seg, tr);
}*/


}