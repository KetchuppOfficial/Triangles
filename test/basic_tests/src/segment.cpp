#include <gtest/gtest.h>

#include "segment.hpp"

using namespace yLab::geometry;

TEST (Segments, Swap_Points)
{
    Point_3D P{1.0, 0.0, 0.0};
    Point_3D Q{0.0, 1.0, 0.0};
    
    Segment seg{P, Q};
    seg.swap_points();

    EXPECT_TRUE (seg.P() == Q && seg.Q() == P);
}

TEST (Segments, Is_Point)
{
    Point_3D pt_1{1.0, 1.0, 1.0};
    EXPECT_THROW ((Segment{pt_1, pt_1}), Segment_Is_Point);

    Point_3D pt_2{-1.0, -1.0, -1.0};
    EXPECT_NO_THROW ((Segment{pt_1, pt_2}));
}
