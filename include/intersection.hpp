#ifndef INCLUDE_INTERSECTION_HPP
#define INCLUDE_INTERSECTION_HPP

#include "triangle.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace Geom_Objects
{

bool intersection_in_2D (const Triangle &tr_1, const Triangle &tr_2);
void point_transformation (Point &point, const Point &origin, const Vector &x_axis,
                           const Vector &y_axis);
void space_transformation (Triangle &tr_1, Triangle &tr_2);
bool test_intersection_R1 (const Triangle &tr_1, const Triangle &tr_2);
bool test_intersection_R2 (const Triangle &tr_1, const Triangle &tr_2);



bool are_intersecting (Triangle &tr_1, Triangle &tr_2);

} // namespace Geom_Objects

#endif // INCLUDE_INTERSECTION_HPP
