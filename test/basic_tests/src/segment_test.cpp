#include "segment.hpp"
#include <gtest/gtest.h>

using namespace Geom_Objects;

TEST(Segment_, ctor_by_triangle)
{
    Point A1 {1.0, 0.0}, B1 {-4.0, 0.0}, C1 {15.0, 0.0};
    Triangle tr1 {A1, B1, C1};

    Point A2 {1.0, 3.0}, B2 {34.0, 102.0}, C2 {11.0, 33.0};
    Triangle tr2 {A2, B2, C2};

    Point A3 {3.0, 4.0}, B3 {-15.0, -14.0}, C3 {7.0, 8.0};
    Triangle tr3 {A3, B3, C3};

    Segment seg1 {tr1};
    Segment seg2 {tr2};
    Segment seg3 {tr3};

    EXPECT_TRUE(seg1.F() == B1 || seg1.S() == C1);
    EXPECT_TRUE(seg1.F() != seg1.S());
    EXPECT_TRUE(seg1.S() == B1 || seg1.S() == C1);

    EXPECT_TRUE(seg2.F() == A2 || seg2.S() == B2);
    EXPECT_TRUE(seg2.F() != seg2.S());
    EXPECT_TRUE(seg2.S() == A2 || seg2.S() == B2);

    EXPECT_TRUE(seg3.F() == B3 || seg3.S() == C3);
    EXPECT_TRUE(seg3.F() != seg3.S());
    EXPECT_TRUE(seg3.S() == B3 || seg3.S() == C3);
}

TEST(Segment_, point_belong_triangle)
{
    Segment F1S1 {Point {3.2}, Point {-5.7}};
    Point A1 {0.0}, B1 {3.7}, C1 {1.0, 0.2};

    Segment F2S2 {Point {-8.0, -8.0}, Point {3.0, 3.0}};
    Point A2 {11.0, 2.0}, B2 {-3.6, -3.6}, C2 {-9.0, -9.0};



}
