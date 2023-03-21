#include <gtest/gtest.h>

#include "point_triangle.hpp"

using namespace yLab::geometry;

TEST (Intersection, Point_Triangle)
{
    Point_3D pt{0.0};

    // point doesn't belong to the plane of triangle
    Triangle tr_1{Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 1.0, 5.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (pt, tr_1));

    // point belongs to the plane of triangle but doesn't belong to triangle itself
    Triangle tr_2{Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, 1.0, 0.0}, Point_3D{1.0, 1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (pt, tr_2));

    // point coincides with a vertex of triangle
    Triangle tr_3{Point_3D{0.0, 0.0, 0.0}, Point_3D{4.0, 12.0, 0.0}, Point_3D{-2.0, 7.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (pt, tr_3));

    // point belongs to a side of triangle
    Triangle tr_4{Point_3D{-1.0, -1.0, 0.0}, Point_3D{1.0, 1.0, 0.0}, Point_3D{1.0, -1.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (pt, tr_4));

    // point belongs to the interior of triangle
    Triangle tr_5{Point_3D{3.0, 3.0, 0.0}, Point_3D{-4.0, 4.0, 0.0}, Point_3D{0.0, -11.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (pt, tr_5));
}
