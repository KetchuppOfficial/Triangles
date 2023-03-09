#ifndef INCLUDE_PRIMITIVES_PRIMITIVE_TRAITS_HPP
#define INCLUDE_PRIMITIVES_PRIMITIVE_TRAITS_HPP

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"

namespace yLab
{

namespace geometry
{

template<typename T>
struct Primitive_Traits final
{
    using distance_type = T;
    using point_type = Point_3D<distance_type>;
    using segment_type = Segment<point_type>;
    using triangle_type = Triangle<point_type>;
};

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_PRIMITIVES_PRIMITIVE_TRAITS_HPP
