#ifndef INCLUDE_TRIANGLE_HPP
#define INCLUDE_TRIANGLE_HPP

#include "point.hpp"
#include "vector.hpp"

#include <algorithm> // for std::swap

namespace Geom_Objects
{

enum Tr_Type {
    _Triangle_,
    _Segment_,
    _Point_,
};


class Triangle
{
    Point P_, Q_, R_;
    Tr_Type type;

    public:
    Triangle (const Point &P, const Point &Q, const Point &R) : P_ {P}, Q_ {Q}, R_ {R}, type {type_calc()} {}

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

    private:
    Tr_Type type_calc() const
    {
        if (is_point())
            return Tr_Type::_Point_;
        else if (is_segment())
            return Tr_Type::_Segment_;
        else
            return Tr_Type::_Triangle_;
    }

    public:
    const Point& P() const & {return P_;}
    const Point& Q() const & {return Q_;}
    const Point& R() const & {return R_;}
    
    Point& P() & {return P_;}
    Point& Q() & {return Q_;}
    Point& R() & {return R_;}

    Vector make_plane_normal() const
    {
        return vector_product(Vector {P_, Q_}, Vector {P_, R_});
    }
};

} // namespace Geom_Objects

#endif // INCLUDE_TRIANGLE_HPP
