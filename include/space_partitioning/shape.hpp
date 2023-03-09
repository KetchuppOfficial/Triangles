#ifndef INCLUDE_SPACE_PARTITIONING_SHAPE_HPP
#define INCLUDE_SPACE_PARTITIONING_SHAPE_HPP

#include <variant>

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "primitive_traits.hpp"
#include "axis_aligned_bounding_box.hpp"

namespace yLab
{

namespace geometry
{

template<typename T>
class Shape
{
public:

    using distance_type = T;
    using point_type = typename Primitive_Traits<distance_type>::point_type;
    using segment_type = typename Primitive_Traits<distance_type>::segment_type;
    using triangle_type = typename Primitive_Traits<distance_type>::triangle_type;
    using primitive_variant = std::variant<point_type, segment_type, triangle_type>;

private:

    primitive_variant primitive_;
    AABB<distance_type> aabb_;

public:

    Shape (const point_type &pt) : primitive_{pt}, aabb_{pt} {}
    Shape (const segment_type &seg) : primitive_{seg}, aabb_{seg.P(), seg.Q()} {}

    template<typename primitive_type>
    Shape (const primitive_type &pr) : primitive_{pr}, aabb_{pr.begin(), pr.end()} {}

    const primitive_variant &primitive () const { return primitive_; }
    primitive_variant &primitive () { return primitive_; }

    const AABB<distance_type> &bounding_volume () const { return aabb_; }
    AABB<distance_type> &bounding_volume () { return aabb_; }
};

template<typename T>
bool are_intersecting (const Shape<T> &shape_1, const Shape<T> &shape_2)
{
    if (are_overlapping (shape_1.bounding_volume(), shape_2.bounding_volume()))
        return true;
    else
    {
        return std::visit ([](auto &primitive_1, auto &primitive_2)
                           {
                               return are_intersecting (primitive_1, primitive_2);
                           },
                           shape_1.primitive(), shape_2.primitive());
    }
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_SHAPE_HPP
