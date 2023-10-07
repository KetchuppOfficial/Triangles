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

    Shape (const segment_type &seg)
          : primitive_{seg}, aabb_{seg.P(), seg.Q()} {}

    template<typename primitive_type>
    Shape (const primitive_type &pr) : primitive_{pr}, aabb_{pr.begin(), pr.end()} {}

    virtual ~Shape () = default;

    const primitive_variant &primitive () const { return primitive_; }
    primitive_variant &primitive () { return primitive_; }

    const AABB<distance_type> &bounding_volume () const { return aabb_; }
    AABB<distance_type> &bounding_volume () { return aabb_; }

    distance_type left_bound (unsigned coord) const
    {
        return aabb_.center()[coord] - aabb_.halfwidth (coord);
    }

    distance_type right_bound (unsigned coord) const
    {
        return aabb_.center()[coord] + aabb_.halfwidth (coord);
    }
};

template<typename T>
class Indexed_Shape : public Shape<T>
{
public:

    using distance_type = T;
    using index_type = std::size_t;

private:

    index_type index_;

public:

    template<typename U>
    Indexed_Shape (const U &primitive, index_type index)
                  : Shape<distance_type>{primitive}, index_{index} {}

    index_type index () const noexcept { return index_; }
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
