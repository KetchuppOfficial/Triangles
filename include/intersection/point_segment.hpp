#ifndef INCLUDE_INTERSECTION_POINT_SEGMENT_HPP
#define INCLUDE_INTERSECTION_POINT_SEGMENT_HPP

#include "point.hpp"
#include "segment.hpp"
#include "vector.hpp"

namespace yLab::geometry
{

namespace detail
{

template<typename T>
bool are_intersecting (const Point_3D<T> &pt, const Segment<Point_3D<T>> &seg)
{
    Vector PQ{seg.P(), seg.Q()};
    Vector PM{seg.P(), pt};

    if (are_collinear (PQ, PM))
    {
        Vector QM{seg.Q(), pt};
        return are_oppositely_directed (PM, QM);
    }
    else
        return false;
}

template<typename T>
bool are_intersecting (const Segment<Point_3D<T>> &seg, const Point_3D<T> &pt)
{
    return are_intersecting (pt, seg);
}

}

} // yLab::geometry

#endif // INCLUDE_INTERSECTION_POINT_SEGMENT_HPP
