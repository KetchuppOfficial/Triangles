#ifndef INCLUDE_INTERSECTION_POINT_POINT_HPP
#define INCLUDE_INTERSECTION_POINT_POINT_HPP

#include "point.hpp"

namespace yLab::geometry
{

template<typename T>
bool are_intersecting (const Point_3D<T> &pt_1, const Point_3D<T> &pt_2)
{
    return pt_1 == pt_2;
}

} // yLab::geometry

#endif // INCLUDE_INTERSECTION_POINT_POINT_HPP
