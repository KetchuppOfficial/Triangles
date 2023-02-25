#include <gtest/gtest.h>

#include "point.hpp"
#include "magic_product.hpp"

using namespace yLab::geometry;
using namespace yLab::geometry::detail;

TEST (Magic_Product, 3D_version)
{
    Point_3D pt_11 {1.0, 0.0, 0.0};
    Point_3D pt_21 {0.0, 1.0, 0.0};
    Point_3D pt_31 {0.0, 0.0, 0.0};

    EXPECT_EQ (magic_product (pt_11, pt_21, pt_31, Point_3D{802.82, -872.85, 48.14}),  Loc_3D::Above);
    EXPECT_EQ (magic_product (pt_11, pt_21, pt_31, Point_3D{802.82, -872.85, 0.0}),    Loc_3D::On);
    EXPECT_EQ (magic_product (pt_11, pt_21, pt_31, Point_3D{802.82, -872.85, -2.865}), Loc_3D::Below);

    EXPECT_EQ (magic_product (pt_11, pt_31, pt_21, Point_3D{802.82, -872.85, 48.14}),  Loc_3D::Below);
    EXPECT_EQ (magic_product (pt_11, pt_31, pt_21, Point_3D{802.82, -872.85, 0.0}),    Loc_3D::On);
    EXPECT_EQ (magic_product (pt_11, pt_31, pt_21, Point_3D{802.82, -872.85, -2.865}), Loc_3D::Above);
}
