#ifndef INCLUDE_SPACE_PARTITIONING_AXIS_ALIGNED_BOUNDING_BOX_HPP
#define INCLUDE_SPACE_PARTITIONING_AXIS_ALIGNED_BOUNDING_BOX_HPP

#include <cmath>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <concepts>

#include "point.hpp"

namespace yLab
{

namespace geometry
{

template<typename T>
class AABB
{
public:

    using distance_type = T;
    using point_type = Point_3D<distance_type>;

private:

    point_type center_;
    distance_type halfwidth_[3];

public:

    AABB (const point_type &center, T x = T{}, T y = T{}, T z = T{})
         : center_{center}, halfwidth_{x, y, z} {}

    AABB (const point_type &pt_1, const point_type &pt_2)
         : center_{(pt_1.x() + pt_2.x()) * distance_type{0.5},
                   (pt_1.y() + pt_2.y()) * distance_type{0.5},
                   (pt_1.z() + pt_2.z()) * distance_type{0.5}},
           halfwidth_{std::abs (pt_1.x() - pt_2.x()) * distance_type{0.5},
                      std::abs (pt_1.y() - pt_2.y()) * distance_type{0.5},
                      std::abs (pt_1.z() - pt_2.z()) * distance_type{0.5}} {}

    template<std::input_iterator it>
    requires std::same_as<point_type, typename std::iterator_traits<it>::value_type>
    AABB (it first, it last) : AABB{point_type{std::min_element (first, last, cmp_x_)->x(),
                                               std::min_element (first, last, cmp_y_)->y(),
                                               std::min_element (first, last, cmp_z_)->z()},
                                    point_type{std::max_element (first, last, cmp_x_)->x(),
                                               std::max_element (first, last, cmp_y_)->y(),
                                               std::max_element (first, last, cmp_z_)->z()}} {}

    const point_type &center () const { return center_; }
    point_type &center () { return center_; }

    distance_type halfwidth (unsigned i) const { return halfwidth_[i]; }

    distance_type halfwidth_x () const { return halfwidth_[0]; }
    distance_type halfwidth_y () const { return halfwidth_[1]; }
    distance_type halfwidth_z () const { return halfwidth_[2]; }

private:

    static constexpr auto cmp_x_ = [](const point_type &P, const point_type &Q)
    {
        return cmp::less (P.x(), Q.x());
    };

    static constexpr auto cmp_y_ = [](const point_type &P, const point_type &Q)
    {
        return cmp::less (P.y(), Q.y());
    };

    static constexpr auto cmp_z_ = [](const point_type &P, const point_type &Q)
    {
        return cmp::less (P.z(), Q.z());
    };
};

template<typename T>
bool are_overlapping (const AABB<T> &first, const AABB<T> &second)
{
    auto &center_1 = first.center();
    auto &center_2 = second.center();

    return cmp::greater (center_1.x() + first.halfwidth_x(), center_2.x() - second.halfwidth_x()) ||
           cmp::greater (center_1.y() + first.halfwidth_y(), center_2.y() - second.halfwidth_y()) ||
           cmp::greater (center_1.z() + first.halfwidth_z(), center_2.z() - second.halfwidth_z());
}

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_AXIS_ALIGNED_BOUNDING_BOX_HPP
