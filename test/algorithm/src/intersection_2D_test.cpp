#include "algorithm_testing.hpp"
#include <gtest/gtest.h>

#include "vector.hpp"
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

    EXPECT_TRUE ((T3.P_ == (Point {0.0, 0.0, 0.0})) &&
                 (T3.Q_ == (Point {2.0*std::sqrt(2.0), 0.0, 0.0})) &&
                 (T3.R_ == (Point {-1 / std::sqrt(2.0), std::sqrt(6) / 2.0, 0.0})));

    EXPECT_TRUE ((T4.P_ == (Point {0.0, std::sqrt(6.0), 0.0})) && 
                 (T4.Q_ == (Point {std::sqrt(2.0), std::sqrt(6.0), 0.0})) &&
                 (T4.R_ == (Point {1 / std::sqrt(2), -std::sqrt(6) / 2.0, 0.0})));
}

TEST(IntersectionTest_2D, Magic_Product)
{
    Triangle T1 { Point {0.0, 0.0, 0.0}, Point {1.0, 0.0, 0.0}, Point {0.0, 1.0, 0.0} };
    Triangle T2 { Point {0.0, 0.0, 0.0}, Point {1.0, 0.0, 0.0}, Point {2.0, 0.0, 0.0} };
    Triangle T3 { Point {0.0, 0.0, 0.0}, Point {0.0, 0.0, 0.0}, Point {0.0, 0.0, 0.0} };

    EXPECT_TRUE (magic_product (T1.P_, T1.Q_, T1.R_) == Loc_2D::Positive &&
                 magic_product (T1.R_, T1.P_, T1.Q_) == Loc_2D::Positive &&
                 magic_product (T1.Q_, T1.R_, T1.P_) == Loc_2D::Positive);

    EXPECT_TRUE (magic_product (T1.Q_, T1.P_, T1.R_) == Loc_2D::Negative &&
                 magic_product (T1.P_, T1.R_, T1.Q_) == Loc_2D::Negative &&
                 magic_product (T1.R_, T1.Q_, T1.P_) == Loc_2D::Negative);

    EXPECT_TRUE (magic_product (T2.P_, T2.Q_, T2.R_) == Loc_2D::Neutral &&
                 magic_product (T2.R_, T2.P_, T2.Q_) == Loc_2D::Neutral &&
                 magic_product (T2.Q_, T2.R_, T2.P_) == Loc_2D::Neutral);

    EXPECT_TRUE (magic_product (T3.P_, T3.Q_, T3.R_) == Loc_2D::Neutral &&
                 magic_product (T3.R_, T3.P_, T3.Q_) == Loc_2D::Neutral &&
                 magic_product (T3.Q_, T3.R_, T3.P_) == Loc_2D::Neutral);
}

TEST (IntersectionTest_2D, Intersection_R1) 
{ 
    Triangle T2   { Point { 2.0, 0.0, 0.0}, Point { 2.0, 3.0, 0.0}, Point { 0.0, 3.0, 0.0}};
    
    Triangle T1_1 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point { 1.0, 1.0, 0.0}};
    Triangle T1_2 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point { 3.0,-1.0, 0.0}};
    Triangle T1_3 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point {-1.0, 4.0, 0.0}};
    Triangle T1_4 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point { 3.0, 1.0, 0.0}};
    Triangle T1_5 { Point {-1.0, 2.0, 0.0}, Point {-1.0, 4.0, 0.0}, Point {-2.0, 4.0, 0.0}};
    Triangle T1_6 { Point {-1.0, 1.0, 0.0}, Point { 4.0,-2.0, 0.0}, Point { 3.0,-1.0, 0.0}};
    Triangle T1_7 { Point {-1.0, 2.0, 0.0}, Point { 3.0, 1.0, 0.0}, Point { 2.0, 4.0, 0.0}};
    Triangle T1_8 { Point {-1.0, 1.0, 0.0}, Point { 4.0,-2.0, 0.0}, Point {-1.0, 2.0, 0.0}};
    Triangle T1_9 { Point {-1.0, 1.0, 0.0}, Point { 4.0,-2.0, 0.0}, Point { 2.0,10.0, 0.0}};

    EXPECT_TRUE (intersection_in_2D (T1_1, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_2, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_3, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_4, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_5, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_6, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_7, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_8, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_9, T2) == true);
}

TEST (IntersectionTest_2D, Intersection_R2)
{
    Triangle T2    { Point { 2.0,  0.0, 0.0}, Point { 0.0, 3.0, 0.0}, Point { 0.0, 0.0, 0.0}};

    Triangle T1_1  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point { 1.0,-1.0, 0.0}};
    Triangle T1_2  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point { 5.0, 1.0, 0.0}};
    Triangle T1_3  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point {-1.0, 2.0, 0.0}};
    Triangle T1_4  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point {-2.0, 1.0, 0.0}};
    Triangle T1_5  { Point {-2.0, -2.0, 0.0}, Point {-1.0,-2.0, 0.0}, Point { 2.0, 3.0, 0.0}};
    Triangle T1_6  { Point {-2.0, -1.0, 0.0}, Point {-1.0,-1.0, 0.0}, Point {-1.0, 3.0, 0.0}};
    Triangle T1_7  { Point {-1.0, -2.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point {-3.0, 0.0, 0.0}};
    Triangle T1_8  { Point {-3.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point {-1.0, 3.0, 0.0}};
    Triangle T1_9  { Point {-3.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point { 1.0, 6.0, 0.0}};
    Triangle T1_10 { Point {-3.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point { 2.0, 6.0, 0.0}};
    Triangle T1_11 { Point {-2.0, -1.0, 0.0}, Point { 1.0, 6.0, 0.0}, Point {-2.0, 4.0, 0.0}};
    Triangle T1_12 { Point {-2.0, -1.0, 0.0}, Point { 2.0, 3.0, 0.0}, Point {-2.0, 4.0, 0.0}};
    Triangle T1_13 { Point {-1.0, -2.0, 0.0}, Point { 5.0, 1.0, 0.0}, Point { 4.0, 1.0, 0.0}};
    Triangle T1_14 { Point {-1.0, -2.0, 0.0}, Point { 5.0, 1.0, 0.0}, Point {-2.0,-2.0, 0.0}};
    Triangle T1_15 { Point {-1.0, -2.0, 0.0}, Point { 5.0, 1.0, 0.0}, Point { 2.0, 2.0, 0.0}};

    EXPECT_TRUE (intersection_in_2D (T1_1, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_2, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_3, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_4, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_5, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_6, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_7, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_8, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_9, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_10, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_11, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_12, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_13, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_14, T2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_15, T2) == true);
}

TEST (IntersectionTest_2D, PartialCase) { 
    Triangle T2   {Point { 2.0, 0.0, 0.0}, Point { 0.0, 3.0, 0.0}, Point { 0.0, 0.0, 0.0}};

    Triangle T1_1 {Point { 0.0, 0.0, 0.0}, Point { 0.0,-3.0, 0.0}, Point {-2.0, 0.0, 0.0}};
    Triangle T1_2 {Point { 2.0, 0.0, 0.0}, Point { 4.0, 0.0, 0.0}, Point { 2.0,-3.0, 0.0}};
    Triangle T1_3 {Point { 0.0, 3.0, 0.0}, Point { 3.0, 3.0, 0.0}, Point { 3.0, 1.0, 0.0}};
    Triangle T1_4 {Point { 1.0, 1.0, 0.0}, Point { 3.0, 1.0, 0.0}, Point { 1.0, 3.0, 0.0}};
    Triangle T1_5 {Point { 1.0, 0.0, 0.0}, Point { 1.0,-2.0, 0.0}, Point { 3.0,-2.0, 0.0}};
    Triangle T1_6 {Point { 0.0, 2.0, 0.0}, Point {-2.0, 4.0, 0.0}, Point {-2.0, 0.0, 0.0}};

    EXPECT_TRUE (intersection_in_2D (T1_1, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_2, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_3, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_4, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_5, T2) == true);
    EXPECT_TRUE (intersection_in_2D (T1_6, T2) == true);
}

TEST (IntersectionTest_2D, Degenerate_Segment_Segment_No_Intersection)
{
    Triangle T1_1 {Point {-1.0, 1.0, 0.0}, Point {0.0, -2.0, 0.0}, Point {0.0, -2.0, 0.0}};
    Triangle T1_2 {Point {-1.0, 1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point {0.0, -2.0, 0.0}};
    Triangle T1_3 {Point {-1.0, 1.0, 0.0}, Point {0.0, -2.0, 0.0}, Point {-1.0, 1.0, 0.0}};

    Triangle T2_1 {Point { 0.0, 0.0, 0.0}, Point { 4.0, 0.0, 0.0}, Point { 4.0, 0.0, 0.0}};
    Triangle T2_2 {Point { 0.0, 0.0, 0.0}, Point { 0.0, 0.0, 0.0}, Point { 4.0, 0.0, 0.0}};
    Triangle T2_3 {Point { 0.0, 0.0, 0.0}, Point { 4.0, 0.0, 0.0}, Point { 0.0, 0.0, 0.0}};

    EXPECT_TRUE (intersection_in_2D (T1_1, T2_1) == false);
    EXPECT_TRUE (intersection_in_2D (T1_1, T2_2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_1, T2_3) == false);
    EXPECT_TRUE (intersection_in_2D (T1_2, T2_1) == false);
    EXPECT_TRUE (intersection_in_2D (T1_2, T2_2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_2, T2_3) == false);
    EXPECT_TRUE (intersection_in_2D (T1_3, T2_1) == false);
    EXPECT_TRUE (intersection_in_2D (T1_3, T2_2) == false);
    EXPECT_TRUE (intersection_in_2D (T1_3, T2_3) == false);
}