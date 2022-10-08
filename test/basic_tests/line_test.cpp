#include <gtest/gtest.h>
#include "line.hpp"

using namespace Geom_Objects;

TEST(Lines, operator_equal)
{
    Point pt1 {1, 1, 1};
    Point pt2 {0, 0, 0};

    Vector vec1 {1, 1, 1};
    Vector vec2 {33, 78, 96};

    Line line1 {pt1, pt2};
    Line line2 {pt1, vec1};
    EXPECT_TRUE(line1 == line2);

    Line line3 {pt1,  vec1};
    Line line4 {pt1, -vec1};
    EXPECT_TRUE(line3 == line4);

    Line line5 {pt2, vec1};
    Line line6 {pt2, vec2};
    EXPECT_TRUE(line5 != line6);
}

TEST(Lines, _are_parallel)
{
    Point pt1 {0, 0, 0};
    Point pt2 {0, 0, 1};

    Vector vec1 {1, 2, 3};
    Vector vec2 {37, 767, -39};

    Line line1 {pt1, vec1};
    Line line2 {pt2, vec1};
    EXPECT_TRUE(are_parallel(line1, line2));

    EXPECT_TRUE(are_parallel(line1, line1)); //basic logic

    Line line3 {pt1, vec1};
    Line line4 {pt1, vec2};
    EXPECT_FALSE(are_parallel(line3, line4));

    Line line5 {pt1,  vec1};
    Line line6 {pt2, -vec1};
    EXPECT_TRUE(are_parallel(line5, line6));

    Line line7 {pt2, vec2};
    EXPECT_FALSE(are_parallel(line3, line7));
}
