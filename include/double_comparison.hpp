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
constexpr bool are_equal (T first, T second, T zero_diff = cmp_precision<T>::epsilon,
                                             T rel_diff  = cmp_precision<T>::epsilon)
{
    auto diff = std::abs (first - second);

    if (diff < zero_diff)
        return true;
    else
        return (diff < std::max (std::abs (first), std::abs (second)) * rel_diff);
}

template<typename T>
constexpr bool is_zero (T value, T zero_diff = cmp_precision<T>::epsilon)
{
    return std::abs (value) < zero_diff;
}

template<typename T>
constexpr bool less (T first, T second, T zero_diff = cmp_precision<T>::epsilon,
                                        T rel_diff  = cmp_precision<T>::epsilon)
{
    return (first < second) && !are_equal (first, second, zero_diff, rel_diff);
}

template<typename T>
constexpr bool less_equal (T first, T second, T zero_diff = cmp_precision<T>::epsilon,
                                              T rel_diff  = cmp_precision<T>::epsilon)
{
    return (first < second) || are_equal (first, second, zero_diff, rel_diff);
}

template<typename T>
constexpr bool greater (T first, T second, T zero_diff = cmp_precision<T>::epsilon,
                                           T rel_diff  = cmp_precision<T>::epsilon)
{
    return (first > second) && !are_equal (first, second, zero_diff, rel_diff);
}

template<typename T>
constexpr bool greater_equal (T first, T second, T zero_diff = cmp_precision<T>::epsilon,
                                                 T rel_diff  = cmp_precision<T>::epsilon)
{
    return (first > second) || are_equal (first, second, zero_diff, rel_diff);
}

} // namespace cmp

} // namespace yLab

#endif // INCLUDE_DOUBLE_COMPARISON_HPP
