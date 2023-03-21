#include <gtest/gtest.h>

#include "segment_segment.hpp"

using namespace yLab::geometry;

TEST (Intersection, Segment_Segment)
{
    Segment seg {Point_3D{-1.0, 0.0, 0.0}, Point_3D{1.0, 0.0, 0.0}};

    // segments belong to crossing lines
    Segment seg_1{Point_3D{0.0, -1.0, 2.0}, Point_3D{0.0, 1.0, 2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg, seg_1));
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg_1, seg));

    // segments belong to intersecting lines
    // ===============================================================

    // one of segments contains the point at which the lines intersect
    // but segments don't intersect
    Segment seg_2{Point_3D{6.0, -5.0, 0.0}, Point_3D{0.0, 5.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg, seg_2));
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg_2, seg));

    // no segment contains the point at which the lines intersect
    Segment seg_3{Point_3D{3.0, 1.0, 0.0}, Point_3D{0.0, 6.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg, seg_3));
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg_3, seg));

    // one end of one segment coincide with one end of the other segment
    Segment seg_4{Point_3D{1.0, 0.0, 0.0}, Point_3D{1.0, 7.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg_4));
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg_4, seg));

    // one end of one segment belongs to the interior of the other segment
    Segment seg_5{Point_3D{0.5, 0.0, 0.0}, Point_3D{0.5, 9.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg_5));
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg_5, seg));

    // segments intersect at a point belonging to the interiors of both segments
    Segment seg_6{Point_3D{-0.4, 2.0, 0.0}, Point_3D{-0.4, -2.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg_6));
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg_6, seg));
    // ===============================================================

    // segments belong to parallel lines
    Segment seg_7{Point_3D{-6.0, -9.0, 0.0}, Point_3D{3.0, -9.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg, seg_7));
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg_7, seg));

    // segments belong to the same line
    // ===============================================================

    // segments don't intersect
    Segment seg_8{Point_3D{2.0, 0.0, 0.0}, Point_3D{3.0, 0.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg, seg_8));
    EXPECT_FALSE (yLab::geometry::are_intersecting (seg_8, seg));

    // {P1   Q1}{P2    Q2}
    Segment seg_9{Point_3D{1.0, 0.0, 0.0}, Point_3D{4.0, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg_9));
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg_9, seg));

    // {P1   Q1}
    //     {P2     Q2}
    Segment seg_10{Point_3D{0.0, 0.0, 0.0}, Point_3D{1.5, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg_10));
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg_10, seg));

    // {P1           Q1}
    //     {P2   Q2}
    Segment seg_11{Point_3D{-7.0, 0.0, 0.0}, Point_3D{2.0, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg_11));
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg_11, seg));

    // {P1   Q1}
    // {P2   Q2}
    EXPECT_TRUE (yLab::geometry::are_intersecting (seg, seg));

    // ===============================================================
}
