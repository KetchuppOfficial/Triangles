#ifndef INCLUDE_SPACE_PARTITIONING_COLLISION_MANAGER
#define INCLUDE_SPACE_PARTITIONING_COLLISION_MANAGER

#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <memory>

#include "point_point.hpp"
#include "point_segment.hpp"
#include "point_triangle.hpp"
#include "segment_segment.hpp"
#include "segment_triangle.hpp"
#include "triangle_triangle.hpp"

#include "shape.hpp"
#include "octree.hpp"

namespace yLab
{

namespace geometry
{

template<typename T, typename U = Indexed_Shape<T>>
class Collision_Manager final
{
public:

    using distance_type = T;
    using shape_type = U;
    using node_type = typename Octree<distance_type, shape_type>::node_type;

private:

    Octree<distance_type> octree_;
    std::vector<node_type *> ancestor_stack_;
    std::set<std::size_t> indexes_; // unique sorted indexes are contained

public:

    template<std::input_iterator it>
    Collision_Manager (it first, it last) : octree_{first, last}
    {
        auto n_shapes = octree_.size();

        ancestor_stack_.reserve (n_shapes);
    }

    void intersect_all () { intersect_all (std::addressof (octree_.root())); }

    void show_intersecting () const
    {
        for (auto &&index : indexes_)
            std::cout << index << " ";
        std::cout << std::endl;
    }

private:

    void intersect_all (node_type *root)
    {
        ancestor_stack_.emplace_back (root);

        for (auto n = 0; n != ancestor_stack_.size(); ++n)
        {
            for (auto &&shape_1 : ancestor_stack_[n]->shapes())
            {
                for (auto &&shape_2 : root->shapes())
                {
                    if (std::addressof (shape_1) == std::addressof (shape_2))
                        break;

                    if (are_intersecting (shape_1, shape_2))
                    {
                        indexes_.emplace(shape_1.index());
                        indexes_.emplace(shape_2.index());
                    }
                }
            }
        }

        for (auto i = 0; i != 8; ++i)
        {
            if (root->child(i))
                intersect_all (root->child(i));
        }

        ancestor_stack_.pop_back();
    }
};

} // namespace geometry

} // namespace yLab

#endif // INCLUDE_SPACE_PARTITIONING_COLLISION_MANAGER
