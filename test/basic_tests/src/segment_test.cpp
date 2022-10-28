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

    EXPECT_TRUE(seg1.F() == B1 || seg1.F() == C1);
    EXPECT_TRUE(seg1.F() != seg1.S());
    EXPECT_TRUE(seg1.S() == B1 || seg1.S() == C1);

    EXPECT_TRUE(seg2.F() == A2 || seg2.F() == B2);
    EXPECT_TRUE(seg2.F() != seg2.S());
    EXPECT_TRUE(seg2.S() == A2 || seg2.S() == B2);

    EXPECT_TRUE(seg3.F() == B3 || seg3.F() == C3);
    EXPECT_TRUE(seg3.F() != seg3.S());
    EXPECT_TRUE(seg3.S() == B3 || seg3.S() == C3);
}

TEST(Segment_, point_belong_triangle_)
{
    Segment seg1 {Point {3.2}, Point {-5.7}};
    Point A1 {0.0}, B1 {3.7}, C1 {1.0, 0.2};

    Segment seg2 {Point {-8.0, -8.0}, Point {3.0, 3.0}};
    Point A2 {11.0, 2.0}, B2 {-3.6, -3.6}, C2 {-9.0, -9.0};

    Segment seg3 {Point {-9.0, -10.0}, Point {3.5, 2.5}};
    Point A3 {3.5, 2.5}, B3 {0.0, 0.0}, C3 {1.0, 0.0};

    EXPECT_TRUE(point_belong_segment(A1, seg1));
    EXPECT_FALSE(point_belong_segment(B1, seg1));
    EXPECT_FALSE(point_belong_segment(C1, seg1));

    EXPECT_FALSE(point_belong_segment(A2, seg2));
    EXPECT_TRUE(point_belong_segment(B2, seg2));
    EXPECT_FALSE(point_belong_segment(C2, seg2));

    EXPECT_TRUE(point_belong_segment(A3, seg3));
    EXPECT_FALSE(point_belong_segment(B3, seg3));
    EXPECT_TRUE(point_belong_segment(C3, seg3));
}

TEST(Segment_, are_intersecting)
{
    /*Segment seg1 {Point {0.0, 0.0}, Point {8.0, 8.0}};
    Segment seg2 {Point {1.0, 0.0}, Point {0.0, 1.0}};
    Segment seg3 {Point {0.0, 0.0, 1.0}, Point {2.0, 2.0, -4.0}};
    Segment seg4 {Point {7.0, 7.0}, Point {2.3, 3.4, 6.7}};
    Segment seg5 {Point {7.0, 7.0}, Point {11.0, 11.0}};
    Segment seg6 {Point {1.0, 0.0}, {9.0, 8.0}};
    Segment seg7 {Point {2.0}, Point {5.0}};
    Segment seg8 {Point {0.0}, Point {1.0}};
    Segment seg9 {Point {3.0, 1.0}, Point {3.0, 5.0}};*/
    Segment seg10 {Point {-2.0}, Point {-0.5}};
    Segment seg11 {Point {3.0}, Point {-1.0, 3.0}};

    /*EXPECT_TRUE(are_intersecting(seg1, seg2));
    EXPECT_TRUE(are_intersecting(seg2, seg1));
    EXPECT_TRUE(are_intersecting(seg1, seg3));
    EXPECT_FALSE(are_intersecting(seg2, seg3));
    EXPECT_TRUE(are_intersecting(seg1, seg4));
    EXPECT_TRUE(are_intersecting(seg1, seg5));
    EXPECT_FALSE(are_intersecting(seg1, seg6));
    EXPECT_FALSE(are_intersecting(seg7, seg8));
    EXPECT_FALSE(are_intersecting(seg7, seg9));*/

    EXPECT_FALSE(are_intersecting(seg10, seg11));
    EXPECT_FALSE(are_intersecting(seg11, seg10));
}

TEST(Segment_, seg_tr_intersecting_2D_)
{
    Triangle tr {Point {-1.0, 3.0}, Point {0.0, 0.0}, Point {3.0, 0.0}};
    Segment seg1 {Point {-1.0, 2.0}, Point {0.5, 2.0}}, seg2 {Point {-2.0, 3.0}, Point {0.0, 3.0}};
    Segment seg3 {Point {3.0, 1.0}, Point {1.5, -1.0}}, seg4 {Point {0.5, -0.5}, Point {0.5, 0.5}};
    Segment seg5 {Point {0.0, 0.0}, Point {2.0, 0.0}}, seg6 {Point {-2.0, 0.0}, Point {-0.5, 0.0}};
    Segment seg7 {Point {2.0, 2.0}, Point {1.0, 3.0}}, seg8 {Point {2.0, 2.0}, Point {-1.5, 3.5}};
    Segment seg9 {Point {-0.5, 3.5}, Point {-1.5, 2.5}}, seg10 {Point {-4.0, 0.0}, Point {5.0, 0.0}};

    EXPECT_TRUE(seg_tr_intersecting_2D(seg1, tr));
    EXPECT_TRUE(seg_tr_intersecting_2D(seg2, tr));
    EXPECT_TRUE(seg_tr_intersecting_2D(seg3, tr));
    EXPECT_TRUE(seg_tr_intersecting_2D(seg4, tr));
    EXPECT_TRUE(seg_tr_intersecting_2D(seg5, tr));
    EXPECT_FALSE(seg_tr_intersecting_2D(seg6, tr));
    EXPECT_FALSE(seg_tr_intersecting_2D(seg7, tr));
    EXPECT_FALSE(seg_tr_intersecting_2D(seg8, tr));
    EXPECT_TRUE(seg_tr_intersecting_2D(seg9, tr));
    EXPECT_TRUE(seg_tr_intersecting_2D(seg10, tr));
}

/*TEST(Segment_, alt_seg_tr_intersecting_2D_)
{
    Triangle tr {Point {-1.0, 3.0}, Point {0.0, 0.0}, Point {3.0, 0.0}};
    Segment seg1 {Point {-1.0, 2.0}, Point {0.5, 2.0}}, seg2 {Point {-2.0, 3.0}, Point {0.0, 3.0}};
    Segment seg3 {Point {3.0, 1.0}, Point {1.5, -1.0}}, seg4 {Point {0.5, -0.5}, Point {0.5, 0.5}};
    Segment seg5 {Point {0.0, 0.0}, Point {2.0, 0.0}}, seg6 {Point {-2.0, 0.0}, Point {-0.5, 0.0}};
    Segment seg7 {Point {2.0, 2.0}, Point {1.0, 3.0}}, seg8 {Point {2.0, 2.0}, Point {-1.5, 3.5}};
    Segment seg9 {Point {-0.5, 3.5}, Point {-1.5, 2.5}}, seg10 {Point {-4.0, 0.0}, Point {5.0, 0.0}};

    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg1, tr));
    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg2, tr));
    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg3, tr));
    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg4, tr));
    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg5, tr));
    EXPECT_FALSE(alt_seg_tr_intersecting_2D(seg6, tr));
    EXPECT_FALSE(alt_seg_tr_intersecting_2D(seg7, tr));
    EXPECT_FALSE(alt_seg_tr_intersecting_2D(seg8, tr));
    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg9, tr));
    EXPECT_TRUE(alt_seg_tr_intersecting_2D(seg10, tr));
}*/

