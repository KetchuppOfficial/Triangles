#include <random>
#include <vector>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <array>
#include <tuple>

#include "primitive_traits.hpp"

using distance_type = float;
using point = yLab::geometry::Primitive_Traits<distance_type>::point_type;

namespace
{

using args = std::tuple<int, distance_type, distance_type, distance_type>;

args cmd_line_args (int argc, char *argv[])
{
    if (argc != 5)
        throw std::runtime_error{"Program requires exactly 4 arguments"};

    auto n_shapes = std::atoi (argv[1]);
    if (n_shapes < 0)
        throw std::runtime_error{"The number of shapes has to be a positive integer"};

    distance_type world_size = std::atof (argv[2]);
    if (yLab::cmp::less_equal (world_size, distance_type{}))
        throw std::runtime_error{"The size of the world has to be a positive number"};

    distance_type min_shape_size = std::atof (argv[3]);
    if (yLab::cmp::less_equal (min_shape_size, distance_type{}))
        throw std::runtime_error{"The minimal size of a shape has to be a positive number"};

    distance_type max_shape_size = std::atof (argv[4]);
    if (yLab::cmp::less_equal (max_shape_size, distance_type{}))
        throw std::runtime_error{"The maximal size of a shape has to be a positive number"};

    if (yLab::cmp::greater_equal (min_shape_size, max_shape_size))
        throw std::runtime_error{"The minimal size of a shape has to be not greater than the maximal one"};

    return std::make_tuple (n_shapes, world_size, min_shape_size, max_shape_size);
}

std::vector<point> generate_points (std::size_t n_shapes, distance_type world_size,
                                                          distance_type min_shape_size,
                                                          distance_type max_shape_size)
{
    using distribution = std::uniform_real_distribution<distance_type>;

    std::vector<point> points;
    points.reserve (n_shapes * 3);

    std::random_device rd;
    std::mt19937_64 gen{rd()};
    distribution coordinate (-world_size, world_size);
    distribution shape_halfwidth (min_shape_size, max_shape_size);

    for (auto i = 0; i != n_shapes; ++i)
    {
        point center{coordinate (gen), coordinate (gen), coordinate (gen)};

        std::array<distance_type, 3> halfwidth_arr {shape_halfwidth (gen), shape_halfwidth (gen),
                                                                           shape_halfwidth (gen)};

        std::array<distribution, 3> axes;
        for (auto i = 0; i != 3; ++i)
            axes[i] = distribution{center[i] - halfwidth_arr[i], center[i] + halfwidth_arr[i]};

        for (auto i = 0; i != 3; ++i)
            points.emplace_back (axes[0](gen), axes[1](gen), axes[2](gen));
    }

    return points;
}

template<std::forward_iterator it>
void dump_points (it first, it last)
{
    std::cout << std::distance (first, last) / 3 << std::endl;

    for (auto point_i = 0; first != last; ++first)
    {
        auto &pt = *first;

        std::cout << pt.x() << " " << pt.y() << " " << pt.z() << " ";
        point_i++;

        if (point_i == 3)
        {
            std::cout << std::endl;
            point_i = 0;
        }
    }
}

} // unnamed namespace

/*
 * argv[1]: the number of shapes
 * argv[2]: the world is a cube each vertex of which is a point (+-argv[2], +-argv[2], +-argv[2])
 * argv[3]: minimal size of bounding boxes
 * argv[4]: maximal size of bounding boxes
 */

int main (int argc, char *argv[])
{
    auto [n_shapes, world_size, min_shape_size, max_shape_size] = cmd_line_args (argc, argv);

    auto points = generate_points (n_shapes, world_size, min_shape_size, max_shape_size);

    dump_points (points.begin(), points.end());

    return 0;
}
