#include <gtest/gtest.h>

#include "intersection.hpp"

using namespace yLab::geometry;

TEST(Intersection, Point_Segment)
{
    Point_3D pt{0.0};

    // point doesn't belong to the line containing segment
    Segment seg_1{Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, -1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (pt, seg_1));

    // point belongs to the line containing segment but not to segment itself
    Segment seg_2{Point_3D{1.0, 1.0, 0.0}, Point_3D{3.0, 3.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (pt, seg_2));

    // point coincides with one end of segment
    Segment seg_3{Point_3D{0.0}, Point_3D{12.0, -14.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (pt, seg_3));

    // point belongs to the interior of segment
    Segment seg_4{Point_3D{-6.0, -6.0, 0.0}, Point_3D{3.0, 3.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (pt, seg_4));
}

TEST (Intersection, Point_Triangle)
{
    Point_3D pt{0.0};

    // point doesn't belong to the plane of triangle
    Triangle tr_1{Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 1.0, 5.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (pt, tr_1));

    // point belongs to the plane of triangle but doesn't belong to triangle itself
    Triangle tr_2{Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (pt, tr_2));

    // point coincides with a vertex of triangle
    Triangle tr_3{Point_3D{0.0, 0.0, 0.0}, Point_3D{4.0, 12.0, 0.0}, Point_3D{-2.0, 7.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (pt, tr_3));

    // point belongs to a side of triangle
    Triangle tr_4{Point_3D{-1.0, -1.0, 0.0}, Point_3D{1.0, 1.0, 0.0}, Point_3D{1.0, -1.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (pt, tr_4));

    // point belongs to the interior of triangle
    Triangle tr_5{Point_3D{3.0, 3.0, 0.0}, Point_3D{-4.0, 4.0, 0.0}, Point_3D{0.0, -11.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (pt, tr_5));
}

TEST (Intersection, Segment_Segment)
{
    Segment seg {Point_3D{-1.0, 0.0, 0.0}, Point_3D{1.0, 0.0, 0.0}};

    // segments belong to crossing lines
    Segment seg_1{Point_3D{0.0, -1.0, 2.0}, Point_3D{0.0, 1.0, 2.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (seg, seg_1));

    // segments belong to intersecting lines
    // ===============================================================

    // one of segments contains the point at which the lines intersect
    // but segments don't intersect
    Segment seg_2{Point_3D{6.0, -5.0, 0.0}, Point_3D{0.0, 5.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (seg, seg_2));

    // no segment contains the point at which the lines intersect
    Segment seg_3{Point_3D{3.0, 1.0, 0.0}, Point_3D{0.0, 6.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (seg, seg_3));

    // one end of one segment coincide with one end of the other segment
    Segment seg_4{Point_3D{1.0, 0.0, 0.0}, Point_3D{1.0, 7.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg_4));

    // one end of one segment belongs to the interior of the other segment
    Segment seg_5{Point_3D{0.5, 0.0, 0.0}, Point_3D{0.5, 9.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg_5));

    // segments intersect at a point belonging to the interiors of both segments
    Segment seg_6{Point_3D{-0.4, 2.0, 0.0}, Point_3D{-0.4, -2.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg_6));
    // ===============================================================

    // segments belong to parallel lines
    Segment seg_7{Point_3D{-6.0, -9.0, 0.0}, Point_3D{3.0, -9.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (seg, seg_7));

    // segments belong to the same line
    // ===============================================================

    // segments don't intersect
    Segment seg_8{Point_3D{2.0, 0.0, 0.0}, Point_3D{3.0, 0.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::detail::are_intersecting (seg, seg_8));

    // {P1   Q1}{P2    Q2}
    Segment seg_9{Point_3D{1.0, 0.0, 0.0}, Point_3D{4.0, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg_9));

    // {P1   Q1}
    //     {P2     Q2}
    Segment seg_10{Point_3D{0.0, 0.0, 0.0}, Point_3D{1.5, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg_10));

    // {P1           Q1}
    //     {P2   Q2}
    Segment seg_11{Point_3D{-7.0, 0.0, 0.0}, Point_3D{2.0, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg_11));

    // {P1   Q1}
    // {P2   Q2}
    EXPECT_TRUE (yLab::geometry::detail::are_intersecting (seg, seg));

    // ===============================================================
}
