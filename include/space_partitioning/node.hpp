#ifndef INCLUDE_SPACE_PARTITIONING_NODE_HPP
#define INCLUDE_SPACE_PARTITIONING_NODE_HPP

#include <cmath>
#include <array>
#include <vector>

#include "vector"
#include "shape.hpp"
#include "primitive_traits.hpp"

namespace yLab
{

namespace geometry
{

template<typename T, typename U = Indexed_Shape<T>>
class Octree_Node final
{
public:

    using distance_type = T;
    using vector_type = Vector<distance_type>;
    using shape_type = U;
    using point_type = typename Primitive_Traits<distance_type>::point_type;

private:

    std::array<Octree_Node *, 8> children_{};
    std::vector<shape_type> shapes_;
    point_type center_;
    distance_type halfwidth_;

public:

    Octree_Node (const point_type &center, distance_type halfwidth)
                : center_{center}, halfwidth_{halfwidth} {}

    // Accessors

    const Octree_Node *child (unsigned child_i) const { return children_[child_i]; }
    Octree_Node *&child (unsigned child_i) { return children_[child_i]; }

    const point_type &center () const { return center_; }
    distance_type halfwidth () const { return halfwidth_; }

    const std::vector<shape_type> &shapes () const { return shapes_; }
    std::vector<shape_type> &shapes () { return shapes_; }

    // Modifiers

    void add_shape (const shape_type &shape) { shapes_.push_back (shape); }
};

namespace detail
{

template<typename T>
void insert_shape (Octree_Node<T> *root, const typename Octree_Node<T>::shape_type &shape)
{
    auto index = 0;
    bool within_range = false;

    auto &bounding_volume = shape.bounding_volume();

    for (auto i = 0; i != 3; ++i)
    {
        auto delta = bounding_volume.center()[i] - root->center()[i];

        if (cmp::less (std::abs (delta), bounding_volume.halfwidth (i)))
        {
            within_range = true;
            break;
        }

        if (cmp::greater (delta, T{}))
            index |= (1 << i);
    }

    if (!within_range && root->child (index))
        insert_shape (root->child (index), shape);
    else
        root->add_shape (shape);
}

} // namespace detail

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_NODE_HPP
