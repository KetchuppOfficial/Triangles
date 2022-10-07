#include "point.hpp"

#include <cmath> // for std::sqrt

namespace Geom_Objects
{

bool are_equal (const Point &first, const Point &second)
{
    return (cmp::are_equal (first.x_, second.x_) && cmp::are_equal (first.y_, second.y_) &&
            cmp::are_equal (first.z_, second.z_));
}

double distance (const Point &first, const Point &second)
{
    if (are_equal (first, second))
        return 0.0;
    else
    {
        auto x_diff = first.x_ - second.x_;
        auto y_diff = first.y_ - second.y_;
        auto z_diff = first.z_ - second.z_;

        return std::sqrt (x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    }
}

} // namespace Geom_Objects
