#include <gtest/gtest.h>

#include "triangle_triangle.hpp"

using namespace yLab::geometry;

TEST (Intersection, Triangle_Triangle_3D)
{
    // (points are referenced by their names after transform_triangle())

    Triangle tr{Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 0.0, 0.0}};

    // planes of triangles are parallel
    Triangle tr_1{Point_3D{0.0, 1.0, 1.0}, Point_3D{1.0, 0.0, 1.0}, Point_3D{0.0, 0.0, 1.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_1));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_1, tr));

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

    // R1 coincides with R2 (Q1R1 intersects with Q2R2 by a point)
    Triangle tr_6{Point_3D{0.0, 1.0, 0.0}, Point_3D{0.0, 2.0, 0.0}, Point_3D{0.0, 1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_6));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_6, tr));

    // Q1 coincides with Q2 (Q1R1 intersects with Q2R2 by a point)
    Triangle tr_7{Point_3D{0.0, -1.0, 0.0}, Point_3D{0.0, 0.0, 0.0}, Point_3D{0.0, -1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_7));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_7, tr));

    // P1 coincides with P2
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

TEST (Intersection, Triangle_Triangle_2D_Easy_Cases)
{
    Triangle tr{Point_3D{0.0, 1.0}, Point_3D{0.0, 0.0}, Point_3D{1.0, 0.0}};

    // P1 belongs to the interior of T2
    Triangle tr_1{Point_3D{0.25, 0.25}, Point_3D{0.25, 1.25}, Point_3D{1.25, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_1, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_1));

    // P1 belongs to a side of T2
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Triangle tr_2{Point_3D{0.5, 0.5}, Point_3D{1.5, 0.5}, Point_3D{0.5, 1.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_2, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_2));

    Triangle tr_3{Point_3D{0.5, 0.0}, Point_3D{0.5, -1.0}, Point_3D{1.5, -1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_3, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_3));

    Triangle tr_4{Point_3D{0.0, 0.5}, Point_3D{-1.0, 0.5}, Point_3D{-1.0, 1.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_4, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_4));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // P1 coincides with a vertex of T2
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Triangle tr_5{Point_3D{0.0, 1.0}, Point_3D{1.0, 1.0}, Point_3D{0.0, 2.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_5, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_5));

    Triangle tr_6{Point_3D{1.0, 0.0}, Point_3D{2.0, 0.0}, Point_3D{1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_6, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_6));

    Triangle tr_7{Point_3D{0.0, 0.0}, Point_3D{-1.0, 0.0}, Point_3D{0.0, -1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_7, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_7));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
}

TEST (Intersection, Triangle_Triangle_2D_R1)
{
    Triangle tr{Point_3D{0.0, 1.0}, Point_3D{0.0, 0.0}, Point_3D{1.0, 0.0}};

    Point_3D P_1{1.0, 1.0}; // belongs to R1

    // Q1 belongs to R11
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Point_3D Q_11{0.5, 1.5};

    // R1 belongs to R11
    Triangle tr_1{P_1, Q_11, Point_3D{0.75, 0.75}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_1, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_1));

    // R1 belongs to RP
    Triangle tr_2{P_1, Q_11, Point_3D{0.5, 0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_2, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_2));

    // R1 belongs to the interior of T2
    Triangle tr_3{P_1, Q_11, Point_3D{0.25, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_3, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_3));

    // R1 is somewhere outside T2 but the intersection takes place
    Triangle tr_4{P_1, Q_11, Point_3D{-0.5, 0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_4, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_4));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // Q1 belongs to R12 (location of R1 doesn't matter
    // as far as points of T1 are counterclockwise oriented)
    Triangle tr_5{P_1, Point_3D{1.5, -1.0}, Point_3D{2.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_5, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_5));

    // Q1 belongs to R13 (location of R1 doesn't matter)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Triangle tr_6{P_1, Point_3D{0.5, 0.5}, Point_3D{0.0, 2.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_6, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_6));

    Triangle tr_7{P_1, Point_3D{0.25, 0.25}, Point_3D{0.0, 2.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_7, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_7));

    Triangle tr_8{P_1, Point_3D{-1.0, -1.0}, Point_3D{0.0, 2.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_8, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_8));

    Triangle tr_9{P_1, Point_3D{1.0, -1.0}, Point_3D{2.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_9, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_9));

    Triangle tr_10{P_1, Point_3D{-1.0, 1.0}, Point_3D{0.0, 2.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_10, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_10));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // Q1 belongs to R14
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Point_3D Q_12{-1.0, 1.5};

    Triangle tr_11{P_1, Q_12, Point_3D{-1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_11, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_11));

    Triangle tr_12{P_1, Q_12, Point_3D{1.0, 0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_12, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_12));

    Triangle tr_13{P_1, Q_12, Point_3D{0.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_13, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_13));

    Triangle tr_14{P_1, Q_12, Point_3D{0.25, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_14, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_14));

    Triangle tr_15{P_1, Q_12, Point_3D{-1.0, -1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_15, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_15));

    Triangle tr_16{P_1, Q_12, Point_3D{-1.0, 1.25}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_16, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_16));

    Triangle tr_17{P_1, Q_12, Point_3D{1.0, 0.75}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_17, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_17));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
}

TEST (Intersection, Triangle_Triangle_2D_R21)
{
    Triangle tr{Point_3D{0.0, 1.0}, Point_3D{0.0, 0.0}, Point_3D{1.0, 0.0}};

    Point_3D P_1{2.0, -0.5}; // belongs to R2
    Point_3D Q_1{2.0, -0.25}; // belongs to R21

    // R1 belongs to R21
    Triangle tr_1{P_1, Q_1, Point_3D{1.0, 1.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_1, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_1));

    // R1 doesn't belong to R21
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_2{P_1, Q_1, Point_3D{-1.0, 2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_2, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_2));

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_3{P_1, Q_1, Point_3D{0.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_3, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_3));

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_4{P_1, Q_1, Point_3D{0.5, 0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_4, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_4));

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_5{P_1, Q_1, Point_3D{1.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_5, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_5));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_6{P_1, Q_1, Point_3D{1.5, -0.5}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_6, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_6));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    // magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_7{P_1, Q_1, Point_3D{-1.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_7, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_7));

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_8{P_1, Q_1, Point_3D{-1.0, 0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_8, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_8));

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_9{P_1, Q_1, Point_3D{-1.0, 1.75}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_9, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_9));

    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_10{P_1, Q_1, Point_3D{-1.5, 2.25}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_10, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_10));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    // magic_product (tr_2.R(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_11{P_1, Q_1, Point_3D{-1.0, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_11, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_11));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_12{P_1, Q_1, Point_3D{-2.0, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_12, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_12));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_13{P_1, Q_1, Point_3D{0.5, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_13, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_13));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_14{P_1, Q_1, Point_3D{0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_14, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_14));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_15{P_1, Q_1, Point_3D{-2.0, 0.125}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_15, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_15));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_16{P_1, Q_1, Point_3D{1.0, 0.0625}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_16, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_16));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_17{P_1, Q_1, Point_3D{1.0, 0.125}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_17, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_17));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_18{P_1, Q_1, Point_3D{-1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_18, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_18));

    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_19{P_1, Q_1, Point_3D{0.0, -1.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_19, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_19));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
}

TEST (Intersection, Triangle_Triangle_2D_R22_or_R25)
{
    Triangle tr{Point_3D{0.0, 1.0}, Point_3D{0.0, 0.0}, Point_3D{1.0, 0.0}};

    Point_3D P_1{2.5, -1.0}; // belongs to R2

    Point_3D Q_11{0.0, -1.0}; // belongs to R22
    // location of R1 doesn't matter as far as points of T1 are counterclockwise oriented
    Triangle tr_1{P_1, Q_11, Point_3D{0.0, -2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_1, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_1));

    // magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Loc_2D::Negative
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Point_3D Q_12{1.0, -0.25}; // belongs to R25

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_2{P_1, Q_12, Point_3D{-0.25, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_2, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_2));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_3{P_1, Q_12, Point_3D{-1.0, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_3, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_3));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_4{P_1, Q_12, Point_3D{0.25, 0.0}};
    //EXPECT_TRUE (yLab::geometry::are_intersecting (tr_4, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_4));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_5{P_1, Q_12, Point_3D{0.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_5, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_5));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_6{P_1, Q_12, Point_3D{0.0, -1.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_6, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_6));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_7{P_1, Q_12, Point_3D{0.5, -0.125}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_7, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_7));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_8{P_1, Q_12, Point_3D{0.5, -0.0625}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_8, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_8));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_9{P_1, Q_12, Point_3D{-1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_9, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_9));

    // magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_2.Q(), tr_1.Q(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_10{P_1, Q_12, Point_3D{-1.0, 0.125}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_10, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_10));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

    // magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Loc_2D::Neutral
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    Point_3D Q_13{0.625, -0.25}; // belongs to the boundary of R25
    // location of R1 doesn't matter as far as points of T1 are counterclockwise oriented
    Triangle tr_11{P_1, Q_13, Point_3D{0.0, -2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_11, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_11));
}

TEST (Intersection, Triangle_Triangle_2D_R24)
{
    Triangle tr{Point_3D{0.0, 1.0}, Point_3D{0.0, 0.0}, Point_3D{1.0, 0.0}};

    Point_3D P_1{2.25, -0.25}; // belongs to R2
    Point_3D Q_1{-1.0, 1.75}; // belongs to R24

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_1{P_1, Q_1, Point_3D{-0.5, -0.5}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_1, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_1));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_2{P_1, Q_1, Point_3D{1.0, 0.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_2, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_2));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_3{P_1, Q_1, Point_3D{-2.25, 2.25}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_3, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_3));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_4{P_1, Q_1, Point_3D{0.0, 1.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_4, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_4));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_5{P_1, Q_1, Point_3D{0.125, 1.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_5, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_5));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral
    Triangle tr_6{P_1, Q_1, Point_3D{-0.5, 1.375}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_6, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_6));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Negative &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Negative
    Triangle tr_7{P_1, Q_1, Point_3D{-1.5, 2.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_7, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_7));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Positive &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_8{P_1, Q_1, Point_3D{0.75, 0.5}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_8, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_8));

    // magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc_2D::Neutral &&
    // magic_product (tr_1.Q(), tr_2.P(), tr_1.R()) == Loc_2D::Positive
    Triangle tr_9{P_1, Q_1, Point_3D{1.125, 0.375}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_9, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_9));
}

TEST (Intersection, Triangle_Triangle_2D_R22_or_R23)
{
    Triangle tr{Point_3D{0.0, 1.0}, Point_3D{0.0, 0.0}, Point_3D{1.0, 0.0}};

    Point_3D P_1{2.0, -0.5}; // belongs to R2
    Point_3D Q_11{-1.0, 1.0}; // belongs to R23
    Point_3D Q_12{-2.0, 0.25}; // belongs to R22
    // location of R_1 doesn't matter as far as points of T1 are counterclockwise oriented
    Point_3D R_1{0.0, -1.0};

    Triangle tr_1{P_1, Q_11, R_1};
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr_1, tr));
    EXPECT_TRUE (yLab::geometry::are_intersecting (tr, tr_1));

    Triangle tr_2{P_1, Q_12, R_1};
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr_2, tr));
    EXPECT_FALSE (yLab::geometry::are_intersecting (tr, tr_2));
}
