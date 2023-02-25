#include <gtest/gtest.h>

#include "double_comparison.hpp"

using namespace yLab::cmp;

TEST (Double_Comparison, Normalized)
{
    EXPECT_TRUE (are_equal (0.0, 0.0));
    EXPECT_TRUE (are_equal (0.0, -0.0));

    EXPECT_FALSE (are_equal (1.0, 0.0));
    EXPECT_FALSE (are_equal (1.0, -0.0));
    EXPECT_FALSE (are_equal (-1.0, 0.0));
    EXPECT_FALSE (are_equal (-1.0, -0.0));

    EXPECT_FALSE (are_equal (83745.2, 0.0));
    EXPECT_FALSE (are_equal (83745.2, -0.0));
    EXPECT_FALSE (are_equal (-83745.2, 0.0));
    EXPECT_FALSE (are_equal (-83745.2, -0.0));
}

TEST (Double_Comparison, Subnormal)
{
    EXPECT_TRUE (are_equal (cmp_precision<double>::epsilon / 2.0, 0.0));
    EXPECT_TRUE (are_equal (cmp_precision<double>::epsilon / 2.0, -0.0));
    EXPECT_TRUE (are_equal (-cmp_precision<double>::epsilon / 2.0, 0.0));
    EXPECT_TRUE (are_equal (-cmp_precision<double>::epsilon / 2.0, -0.0));

    EXPECT_TRUE (are_equal (1e-10, 0.0));
    EXPECT_TRUE (are_equal (1e-10, -0.0));
    EXPECT_TRUE (are_equal (-1e-10, 0.0));
    EXPECT_TRUE (are_equal (-1e-10, -0.0));
}
