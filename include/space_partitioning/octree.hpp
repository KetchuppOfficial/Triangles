#ifndef INCLUDE_SPACE_PARTITIONING_OCTREE_HPP
#define INCLUDE_SPACE_PARTITIONING_OCTREE_HPP

#include <vector>
#include <cmath>
#include <exception>
#include <iterator>
#include <utility>
#include <tuple>
#include <iostream>

#include "shape.hpp"
#include "node.hpp"
#include "primitive_traits.hpp"

namespace yLab
{

namespace geometry
{

template<typename, typename> class Octree;

namespace detail
{

inline std::size_t pseudo_optimal_height (std::size_t n_shapes)
{
    return std::max (std::size_t(1), static_cast<std::size_t>(std::log10 (1 + n_shapes)));
}

template<std::input_iterator it>
auto calculate_octree_parameters (it first, it last)
{
    using shape_type = typename std::iterator_traits<it>::value_type;
    using distance_type = typename shape_type::distance_type;
    using size_type = typename Octree<distance_type, shape_type>::size_type;
    
    std::array<distance_type, 3> min{};
    std::array<distance_type, 3> max{};
    
    std::size_t n_shapes = 0;
    for (; first != last; ++first, ++n_shapes)
    {
        auto &bounding_volume = (*first).bounding_volume();
        auto &center = bounding_volume.center();

        for (auto i = 0; i != 3; ++i)
        {
            auto left_border_i = center[i] - bounding_volume.halfwidth(i);
            auto right_border_i = center[i] + bounding_volume.halfwidth(i);

            if (cmp::less (left_border_i, min[i]))
                min[i] = left_border_i;

            if (cmp::greater (right_border_i, max[i]))
                max[i] = right_border_i;
        }
    }

    auto less = [](distance_type &first, distance_type &second){ return cmp::less(first, second); };

    auto min_elem = std::min_element (min.begin(), min.end(), less);
    auto max_elem = std::max_element (max.begin(), max.end(), less);

    auto pt_coord = (*min_elem + *max_elem) / distance_type{2};
    auto halfwidht = (*max_elem - *min_elem) / distance_type{2};

    auto height = std::min (Octree<distance_type, shape_type>::max_height(),
                            pseudo_optimal_height (n_shapes));

    return std::tuple{Point_3D{pt_coord, pt_coord, pt_coord}, halfwidht, height};
}

} // namespace detail

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
    
    template<std::input_iterator it>
    Octree (it first, it last)
    {
        if (first == last)
            throw Empty_Octree{};
        
        auto [center, halfwidth, height] = detail::calculate_octree_parameters (first, last);
        height_ = height;

        nodes_.reserve (max_size());
        build_subtree (center, halfwidth, height);

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
    requires std::same_as<std::iter_value_t<it>, shape_type>
    void insert (it first, it last)
    {
        for (; first != last; ++first)
            insert (*first);
    }

    const node_type &root () const { return nodes_.front(); }
    node_type &root () { return nodes_.front(); }

private:

    node_type *build_subtree (const point_type &center, distance_type halfwidth, unsigned stop_depth)
    {
        node_type &subroot = nodes_.emplace_back(center, halfwidth);
        
        if (stop_depth > 1)
        {
            auto step = halfwidth * distance_type{0.5};
            for (int child_i = 0; child_i != 8; ++child_i)
            {
                point_type offset {(child_i & 1) ? step : -step,
                                   (child_i & 2) ? step : -step,
                                   (child_i & 4) ? step : -step};

                point_type new_center{center.x() + offset.x(), center.y() + offset.y(),
                                      center.z() + offset.z()};

                subroot.child (child_i) = build_subtree (new_center, step, stop_depth - 1);
            }
        }

        return std::addressof (subroot);
    }
};

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_OCTREE_HPP
