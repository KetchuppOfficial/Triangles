#include "intersection.hpp"
#include <gtest/gtest.h>

#include "double_comparison.hpp"

using namespace Geom_Objects;

TEST(IntersectionTest_2D, SpaceTransformation)
{
    Triangle T1 { Point {0.0, 0.0, 1223.0}, Point {2.0, 0.0, 1223.0}, Point {0.0, 1.0, 1223.0}};
    Triangle T2 { Point {3.0, 0.0, 1223.0}, Point {4.0, 0.0, 1223.0}, Point {4.0, 2.0, 1223.0}};

    Triangle T3 { Point {1.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point {2.0, -1.0, -1.0}};
    Triangle T4 { Point {2.0, 0.0, -2.0}, Point {1.0, 1.0, -2.0}, Point {0.0, -1.0, 1.0}};

    space_transformation (T1, T2);

    EXPECT_TRUE ((T1.P_ == (Point {0.0, 0.0, 0.0})) && 
                 (T1.Q_ == (Point {2.0, 0.0, 0.0})) &&
                 (T1.R_ == (Point {0.0, 1.0, 0.0})));

    EXPECT_TRUE ((T2.P_ == (Point {3.0, 0.0, 0.0})) && 
                 (T2.Q_ == (Point {4.0, 0.0, 0.0})) &&
                 (T2.R_ == (Point {4.0, 2.0, 0.0})));

    space_transformation (T3, T4);

    EXPECT_TRUE (cmp::are_equal(T3.P_.x_, 0.0) &&
                 cmp::are_equal(T3.P_.y_, 0.0) &&
                 cmp::are_equal(T3.P_.z_, 0.0));

    EXPECT_TRUE (cmp::are_equal(T3.Q_.x_, -2.0*std::sqrt(2)) &&
                 cmp::are_equal(T3.Q_.y_, 0.0) &&
                 cmp::are_equal(T3.Q_.z_, 0.0));

    EXPECT_TRUE (cmp::are_equal(T3.R_.x_, 1 / std::sqrt(2)) &&
                 cmp::are_equal(T3.R_.y_, std::sqrt(6) / 2.0) &&
                 cmp::are_equal(T3.R_.z_, 0.0));

    // EXPECT_TRUE ((T3.P_ == (Point {0.0, 0.0, 0.0})) && 
    //              (T3.Q_ == (Point {-2.0*std::sqrt(2), 0.0, 0.0})) &&
    //              (T3.R_ == (Point {1 / std::sqrt(2), std::sqrt(6) / 2.0, 0.0})));

    // EXPECT_TRUE ((T4.P_ == (Point {0.0, std::sqrt(6), 0.0})) && 
    //              (T4.Q_ == (Point {-std::sqrt(2), std::sqrt(6), 0.0})) &&
    //              (T4.R_ == (Point {-1 / std::sqrt(2), -std::sqrt(6) / 2.0, 0.0})));

}
