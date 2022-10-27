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
        if (scalar_product(seg1.FS(), seg2_cpy.FS()) < 0)
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

}