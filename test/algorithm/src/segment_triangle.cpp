#include <gtest/gtest.h>

#include "segment_triangle.hpp"

using namespace yLab::geometry;

TEST (Intersection, Segment_Triangle)
{
    Triangle tr{Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 0.0, 0.0}};

    // segment and triangle aren't coplanar
    // ================================================================

    // segment locates above the plane of triangle
    Segment seg_1{Point_3D{0.3, 0.3, 1.0}, Point_3D{0.3, 0.0, 2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, seg_1));

    // one end of segment belongs to the interior of triangle
    Segment seg_2{Point_3D{0.1, 0.2, 0.0}, Point_3D{4.0, -3.0, 2.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_2));

    // one end of segment coincides with a vertex of triangle
    Segment seg_3{Point_3D{0.0, 0.0, 0.0}, Point_3D{1.0, -13.0, -6.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_3));

    // one end of segment belongs to a side of triangle
    Segment seg_4{Point_3D{0.5, 0.0, 0.0}, Point_3D{4.0, 11.3, 0.7}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_4));

    // a vertex of triangle belongs to the interior of segment
    Segment seg_5{Point_3D{0.0, 0.0, -1.0}, Point_3D{0.0, 0.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_5));

    // a side of triangle intersects with the interior of segment
    Segment seg_6{Point_3D{0.5, 0.0, -1.0}, Point_3D{0.5, 0.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_6));

    // segment and triangle intersect by their interiors
    Segment seg_7{Point_3D{0.3, 0.3, -1.0}, Point_3D{0.3, 0.3, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_7));

    // ================================================================

    // segment and triangle are coplanar
    // ================================================================

    // one end of segment belongs to the interior of triangle
    Segment seg_8{Point_3D{0.3, 0.3, 0.0}, Point_3D{2.0, 2.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_8));

    // one end of segment belongs to a side of triangle
    Segment seg_9{Point_3D{0.5, 0.0, 0.0}, Point_3D{0.5, -2.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_9));

    // one end of segment coincides with a vertex of triangle
    Segment seg_10{Point_3D{1.0, 0.0, 0.0}, Point_3D{2.0, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_10));

    // seg.P_ belongs to R1, seg.Q_ belongs to R1
    Segment seg_11{Point_3D{1.0, 1.0, 0.0}, Point_3D{2.0, 2.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, seg_11));

    // seg.P belongs to R1, seg.Q_ belongs to RP-side of triangle
    Segment seg_12{Point_3D{1.0, 1.0, 0.0}, Point_3D{0.5, 0.5, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_12));

    // seg.P belongs to R1, seg.Q_ belongs to R12
    Segment seg_13{Point_3D{1.0, 1.0, 0.0}, Point_3D{1.5, -1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, seg_13));

    // seg.P belongs to R1, seg.Q_ belongs to R13
    Segment seg_14{Point_3D{1.0, 1.0, 0.0}, Point_3D{-1.0, -1.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, seg_14));

    // seg.P belongs to R1, seg.Q_ belongs to R14
    Segment seg_15{Point_3D{1.0, 1.0, 0.0}, Point_3D{-1.0, 1.5, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, seg_15));

    // ================================================================
}
