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

} // namespace Geom_Objects

#endif // INCLUDE_TRIANGLE_HPP
