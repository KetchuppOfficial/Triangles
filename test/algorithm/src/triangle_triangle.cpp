#include <gtest/gtest.h>

#include "triangle_triangle.hpp"

using namespace yLab::geometry;

TEST (Intersection, Triangle_Triangle_3D)
{
    Triangle tr{Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 0.0, 0.0}};

    // planes of triangles are parallel
    Triangle tr_1{Point_3D{0.0, 1.0, 1.0}, Point_3D{1.0, 0.0, 1.0}, Point_3D{0.0, 0.0, 1.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_1));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_1, tr));

    // triangles aren't coplanar
    // (points are referenced by their names after transform_triangle())
    // ================================================================

    // no triangle intersect the plane of the other one
    Triangle tr_2{Point_3D{-1.0, 0.0, 0.0}, Point_3D{-1.0, 1.0, 0.0}, Point_3D{-1.0, 0.0, 2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_2));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_2, tr));

    // planes of triangles intersect but triangles themselves don't
    Triangle tr_3{Point_3D{-1.0, 0.0, -0.5}, Point_3D{-1.0, 1.0, -0.5}, Point_3D{-1.0, 0.0, 1.5}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_3));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_3, tr));

    // QR sides of both triangles coincide
    Triangle tr_4{Point_3D{0.0, 0.0, 0.0}, Point_3D{0.0, 1.0, 0.0}, Point_3D{0.0, 0.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_4));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_4, tr));

    // QR sides of both triangles overlap
    Triangle tr_5{Point_3D{0.0, 0.5, 0.0}, Point_3D{0.0, 1.5, 0.0}, Point_3D{0.0, 0.5, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_5));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_5, tr));

    // R1 coinsides with R2 (Q1R1 intersects with Q2R2 by a point)
    Triangle tr_6{Point_3D{0.0, 1.0, 0.0}, Point_3D{0.0, 2.0, 0.0}, Point_3D{0.0, 1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_6));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_6, tr));

    // Q1 coinsides with Q2 (Q1R1 intersects with Q2R2 by a point)
    Triangle tr_7{Point_3D{0.0, -1.0, 0.0}, Point_3D{0.0, 0.0, 0.0}, Point_3D{0.0, -1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_7));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_7, tr));

    // P1 coinsides with P2
    Triangle tr_8{Point_3D{1.0, 0.0, -1.0}, Point_3D{1.0, 1.0, -1.0}, Point_3D{1.0, 0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_8));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_8, tr));

    // Segments belonging to the interiors of triangles coincide 
    Triangle tr_9{Point_3D{0.5, 0.0, -0.5}, Point_3D{0.5, 1.0, -0.5}, Point_3D{0.5, 0.0, 5.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_9));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_9, tr));

    // Segments belonging to the interiors of triangles overlap
    Triangle tr_10{Point_3D{0.5, 0.25, -0.5}, Point_3D{0.5, 1.25, -0.5}, Point_3D{0.5, 0.25, 5.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_10));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_10, tr));

    // Segments belonging to the interiors of triangles overlap by a point (case 1)
    Triangle tr_11{Point_3D{0.5, 0.5, -0.5}, Point_3D{0.5, 1.5, -0.5}, Point_3D{0.5, 0.5, 5.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_11));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_11, tr));

    // Segments belonging to the interiors of triangles overlap by a point (case 2)
    Triangle tr_12{Point_3D{0.5, -0.5, -0.5}, Point_3D{0.5, 5.0, -0.5}, Point_3D{0.5, -0.5, 5.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_12));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_12, tr));

    // A segment belonging to the interior of one triangle belongs to such segment of the other triangle
    Triangle tr_13{Point_3D{0.5, 0.125, -0.5}, Point_3D{0.5, 0.625, -0.5}, Point_3D{0.5, 0.125, 0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_13));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_13, tr));

    // Triangles don't intersect
    Triangle tr_14{Point_3D{0.5, 1.0, -0.5}, Point_3D{0.5, 2.0, -0.5}, Point_3D{0.5, 1.0, 0.5}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_14));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_14, tr));

    // ================================================================
}
