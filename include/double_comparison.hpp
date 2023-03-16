#ifndef INCLUDE_DOUBLE_COMPARISON_HPP
#define INCLUDE_DOUBLE_COMPARISON_HPP

#include <algorithm>
#include <cmath>
#include <type_traits>

namespace yLab
{

namespace cmp
{

template<typename T>
requires std::is_floating_point_v<T>
struct cmp_precision final
{
    static constexpr T epsilon = 1e-6;
};

template<typename T>
requires std::is_floating_point_v<T>
bool are_equal (T first, T second, T zero_diff = cmp_precision<T>::epsilon, 
                                   T rel_diff  = cmp_precision<T>::epsilon)
{
    auto diff = std::abs (first - second);

    if (diff < zero_diff)
        return true;
    else
        return (diff < std::max (std::abs (first), std::abs (second)) * rel_diff);
}

template<typename T>
bool is_zero (T value) { return are_equal (value, T{}); }

template<typename T>
bool less (T first, T second) { return (first < second) && !are_equal (first, second); }

template<typename T>
bool less_equal (T first, T second) { return (first < second) || are_equal (first, second); }

template<typename T>
bool greater (T first, T second) { return (first > second) && !are_equal (first, second); }

template<typename T>
bool greater_equal (T first, T second) { return (first > second) || are_equal (first, second); }

} // namespace cmp

} // namespace yLab

#endif // INCLUDE_DOUBLE_COMPARISON_HPP
