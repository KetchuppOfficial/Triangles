#ifndef INCLUDE_SPACE_PARTITIONING_INTERSECTOR
#define INCLUDE_SPACE_PARTITIONING_INTERSECTOR

#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include <algorithm>
#include <utility>

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

template<typename T>
class Intersector final
{
public:

    using distance_type = T;
    using node_type = typename Octree<distance_type>::node_type;

private: 
    
    Octree<distance_type> octree_;
    std::vector<node_type *> ancestor_stack_;

public:

    template<std::input_iterator it>
    Intersector (it first, it last) : octree_{first, last}
    {
        ancestor_stack_.reserve (octree_.max_size());
    }

    void intersect_all () { intersect_all (std::addressof (octree_.root())); }

private:

    void intersect_all (node_type *root)
    {
        ancestor_stack_.push_back (root);

        for (auto n = 0; n != ancestor_stack_.size(); ++n)
            for (auto &&shape_1 : ancestor_stack_[n]->shapes())
                for (auto &&shape_2 : root->shapes())
                {
                    if (std::addressof(shape_1) == std::addressof (shape_2))
                        break;

                    if (are_intersecting (shape_1, shape_2))
                    {
                        std::visit([](auto &&primitive_1, auto &&primitive_2)
                                   {
                                        std::cout << primitive_1 << " and "
                                                  << primitive_2 << " intersect;" << std::endl;
                                   }, shape_1.primitive(), shape_2.primitive());
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

#endif // INCLUDE_SPACE_PARTITIONING_INTERSECTOR
