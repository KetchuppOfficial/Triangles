#ifndef INCLUDE_SPACE_PARTITIONING_OCTREE_HPP
#define INCLUDE_SPACE_PARTITIONING_OCTREE_HPP

#include <vector>
#include <cmath>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <iostream>
#include <array>
#include <memory>
#include <numeric>

#include "shape.hpp"
#include "node.hpp"
#include "primitive_traits.hpp"

namespace yLab
{

namespace geometry
{

struct Empty_Octree final: public std::runtime_error
{
    Empty_Octree () : std::runtime_error{"Octree can't be constructed if no shapes are provided"} {}
};

template<typename T, typename U = Indexed_Shape<T>>
class Octree final
{
public:

    using distance_type = T;
    using point_type = typename Primitive_Traits<T>::point_type;
    using shape_type = U;
    using node_type = Octree_Node<distance_type, shape_type>;
    using size_type = std::size_t;

private:

    std::vector<node_type> nodes_;
    size_type height_;

public:

    template<std::forward_iterator it>
    Octree (it first, it last)
    {
        if (first == last)
            throw Empty_Octree{};

        auto n_shapes = std::distance(first, last);
        nodes_.reserve (n_shapes);
        height_ = std::min (max_height(), pseudo_optimal_height (n_shapes));

        auto [center, halfwidth] = calculate_octree_parameters (first, last);

        build_subtree (center, halfwidth, height_);
        insert (first, last);
    }

    size_type height () const noexcept { return height_; }
    static constexpr size_type max_height () noexcept { return 6; }

    size_type size () const noexcept { return nodes_.size(); }
    size_type max_size () const
    {
        return (static_cast<size_type>(std::exp2 (3 * height())) - 1) / (8 - 1);
    }

    // Modifiers

    void insert (const shape_type &shape)
    {
        detail::insert_shape (std::addressof (root()), shape);
    }

    template<std::input_iterator it>
    requires std::same_as<shape_type, typename std::iterator_traits<it>::value_type>
    void insert (it first, it last)
    {
        for (; first != last; ++first)
            insert (*first);
    }

    const node_type &root () const { return nodes_.front(); }
    node_type &root () { return nodes_.front(); }

private:

    static std::size_t pseudo_optimal_height (std::size_t n_shapes)
    {
        return std::max (std::size_t{1}, static_cast<std::size_t>(std::log10 (1 + n_shapes)));
    }

    template<std::input_iterator it>
    static auto calculate_octree_parameters (it first, it last)
    {
        auto less = [](distance_type first, distance_type second)
        {
            return cmp::less(first, second);
        };

        std::array<distance_type, 3> min{first->left_bound (0),
                                         first->left_bound (1),
                                         first->left_bound (2)};
        std::array<distance_type, 3> max{first->right_bound (0),
                                         first->right_bound (1),
                                         first->right_bound (2)};

        for (++first; first != last; ++first)
        {
            for (auto i = 0; i != 3; ++i)
            {
                min[i] = std::min (first->left_bound (i), min[i], less);
                max[i] = std::max (first->right_bound (i), max[i], less);
            }
        }

        distance_type min_elem = *std::min_element (min.begin(), min.end(), less);
        distance_type max_elem = *std::max_element (max.begin(), max.end(), less);

        distance_type pt_coord = std::midpoint(min_elem, max_elem);
        distance_type halfwidth = (max_elem - min_elem) / 2;

        return std::pair{Point_3D{pt_coord, pt_coord, pt_coord}, halfwidth};
    }

    node_type *build_subtree (const point_type &center, distance_type halfwidth,
                              unsigned stop_depth)
    {
        node_type &subroot = nodes_.emplace_back(center, halfwidth);

        if (stop_depth > 1)
        {
            distance_type step = halfwidth * 0.5;
            for (int i = 0; i != 8; ++i)
            {
                point_type new_center{center.x() + (i & 1) ? step : -step,
                                      center.y() + (i & 2) ? step : -step,
                                      center.z() + (i & 4) ? step : -step};

                subroot.child (i) = build_subtree (new_center, step, stop_depth - 1);
            }
        }

        return std::addressof (subroot);
    }
};

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_OCTREE_HPP
