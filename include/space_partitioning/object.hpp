#ifndef INLCLUDE_SPACE_PARTITIONING_OBJECT_HPP
#define INLCLUDE_SPACE_PARTITIONING_OBJECT_HPP

#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "axis_aligned_bounding_box.hpp"

namespace yLab
{

namespace geometry
{

// primitive_type::point_type is always Point_3D as far as it is required in AABB contructor
template<typename T>
class Object
{
public:

    using primitive_type = T;
    using distance_type = typename primitive_type::point_type::distance_type;

private:

    primitive_type primitive_;
    AABB<distance_type> aabb_;

public:

    Object (const primitive_type &primitive) : primitive_{primitive}, 
                                  aabb_{primitive.begin(), primitive.end()} {}

    const primitive_type &primitive () const { return primitive_; }
    primitive_type &primitive () { return primitive_; }

    const AABB<distance_type> &aabb () const { return aabb_; }
    AABB<distance_type> &aabb () { return aabb_; }
};

template<typename T>
class Object<Segment<Point_3D<T>>>
{
public:

    using distance_type = T;
    using primitive_type = Segment<Point_3D<distance_type>>;

private:

    primitive_type segment_;
    AABB<distance_type> aabb_;

public:

    Object (const primitive_type &primitive)
           : segment_{primitive}, aabb_{segment_.P(), segment_.Q()} {}

    const primitive_type &primitive () const { return segment_; }
    primitive_type &primitive () { return segment_; }

    const AABB<distance_type> &aabb () const { return aabb_; }
    AABB<distance_type> &aabb () { return aabb_; }
};

template<typename T>
class Object<Point_3D<T>>
{
public:

    using distance_type = T;
    using primitive_type = Point_3D<distance_type>;

private:    
    
    AABB<distance_type> aabb_;

public:

    Object (const primitive_type &primitive) : aabb_{primitive} {}

    const primitive_type &primitive () const { return aabb_.center(); }
    primitive_type &primitive () { return aabb_.center(); }

    const AABB<distance_type> &aabb () const { return aabb_; }
    AABB<distance_type> &aabb () { return aabb_; }
};

} // geometry

} // namespace yLab

#endif // INLCLUDE_SPACE_PARTITIONING_OBJECT_HPP
