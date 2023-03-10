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

    try
    {
        Segment seg_1{pt_1, pt_1};
        EXPECT_TRUE (false);
    }
    catch (Segment_Is_Point &expt) { EXPECT_TRUE (true); }
    catch (...) { EXPECT_TRUE (false); }

    Point_3D pt_2{-1.0, -1.0, -1.0};

    try
    {
        Segment seg_2{pt_1, pt_2};
        EXPECT_TRUE (true);
    }
    catch (Segment_Is_Point &expt) { EXPECT_TRUE (false); }
    catch (...) { EXPECT_TRUE (false); }
}
