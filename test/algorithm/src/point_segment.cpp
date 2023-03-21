#include <gtest/gtest.h>

#include "point_segment.hpp"

using namespace yLab::geometry;

TEST(Intersection, Point_Segment)
{
    Point_3D pt{0.0};

    // point doesn't belong to the line containing segment
    Segment seg_1{Point_3D{1.0, 0.0, 0.0}, Point_3D{0.0, -1.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (pt, seg_1));

    // point belongs to the line containing segment but not to segment itself
    Segment seg_2{Point_3D{1.0, 1.0, 0.0}, Point_3D{3.0, 3.0, 0.0}};
    EXPECT_FALSE (yLab::geometry::are_intersecting (pt, seg_2));

    // point coincides with one end of segment
    Segment seg_3{Point_3D{0.0}, Point_3D{12.0, -14.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (pt, seg_3));

    // point belongs to the interior of segment
    Segment seg_4{Point_3D{-6.0, -6.0, 0.0}, Point_3D{3.0, 3.0, 0.0}};
    EXPECT_TRUE (yLab::geometry::are_intersecting (pt, seg_4));
}
