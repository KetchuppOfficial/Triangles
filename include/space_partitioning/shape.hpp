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
class Shape final
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

    // This member is needed to pass tests where the indexes of shapes should be outputed
    std::size_t index;

    Shape (const point_type &pt, std::size_t i = 0)
          : primitive_{pt}, aabb_{pt}, index{i} {}

    Shape (const segment_type &seg, std::size_t i = 0)
          : primitive_{seg}, aabb_{seg.P(), seg.Q()}, index{i} {}

    template<typename primitive_type>
    Shape (const primitive_type &pr, std::size_t i = 0)
          : primitive_{pr}, aabb_{pr.begin(), pr.end()}, index{i} {}

    const primitive_variant &primitive () const { return primitive_; }
    primitive_variant &primitive () { return primitive_; }

    const AABB<distance_type> &bounding_volume () const { return aabb_; }
    AABB<distance_type> &bounding_volume () { return aabb_; }
};

template<typename T>
bool are_intersecting (const Shape<T> &shape_1, const Shape<T> &shape_2)
{
    if (are_overlapping (shape_1.bounding_volume(), shape_2.bounding_volume()))
    {
        return std::visit ([](auto &primitive_1, auto &primitive_2)
                           {
                               return are_intersecting (primitive_1, primitive_2);
                           },
                           shape_1.primitive(), shape_2.primitive());
    }
    else
        return false;
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_SHAPE_HPP
