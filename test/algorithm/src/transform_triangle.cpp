#include <gtest/gtest.h>

#include "point.hpp"
#include "triangle.hpp"

#include "triangle_triangle.hpp"

using namespace yLab::geometry;
using namespace yLab::geometry::detail;

#define COMMON_PART                                                                                                \
do                                                                                                                 \
{                                                                                                                  \
    auto [tr_1_, tr_2_] = transform_triangle (tr_1, magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P()),        \
                                                    magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.Q()),        \
                                                    magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.R()), tr_2); \
                                                                                                                   \
    EXPECT_TRUE (new_tr_1 == tr_1_);                                                                               \
    EXPECT_TRUE (new_tr_2 == tr_2_);                                                                               \
}                                                                                                                  \
while (0)

// P_loc == Loc_3D::Above
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST (Transform_Triangle, P_Above__Q_Above__R_On)
{
    Triangle tr_1 {Point_3D{-12.0, 13.0, 4.0},
                   Point_3D{  8.0, -5.0, 3.0},
                   Point_3D{  5.0, -7.0, 0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_Above__R_Below)
{
    Triangle tr_1 {Point_3D{71.0,   5.0, 10.0},
                   Point_3D{-2.0,   1.0, 14.0},
                   Point_3D{ 8.0, -20.0, -9.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_On__R_Above)
{
    Triangle tr_1 {Point_3D{  7.0, -9.0, 11.0},
                   Point_3D{-34.0, 16.0,  0.0},
                   Point_3D{-28.0,  3.0,  8.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_On__R_On)
{
    Triangle tr_1 {Point_3D{ -1.0,  7.0, 5.0},
                   Point_3D{-22.0, 15.0, 0.0},
                   Point_3D{ 18.0,  6.0, 0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},  
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_On__R_Below)
{
    Triangle tr_1 {Point_3D{17.0, -2.0,  37.0},
                   Point_3D{ 4.0, 12.0,   0.0},
                   Point_3D{ 0.0, 10.0, -56.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_Below__R_Above)
{
    Triangle tr_1 {Point_3D{13.0, -24.0,  11.0}, 
                   Point_3D{ 3.0, -46.0, -25.0},
                   Point_3D{ 9.0,  -4.0,   8.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_Below__R_On)
{
    Triangle tr_1 {Point_3D{-38.0, 41.0,  67.0},
                   Point_3D{ -1.0, -8.0, -31.0},
                   Point_3D{  5.0,  9.0,   0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triagle, P_Above__Q_Below__R_Below)
{
    Triangle tr_1 {Point_3D{  4.0,  14.0,  13.0},
                   Point_3D{ 71.0, -35.0, -15.0},
                   Point_3D{-16.0,  23.0, -18.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// P_loc == Loc_3D::On
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST (Transform_Triangle, P_On__Q_Above__R_Above)
{
    Triangle tr_1 {Point_3D{-18.0,  71.0,  0.0},
                   Point_3D{  1.0,   5.0, 35.0},
                   Point_3D{  9.0, -43.0, 11.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Above__R_On)
{
    Triangle tr_1 {Point_3D{ 4.0,  -6.0,  0.0},
                   Point_3D{52.0, -37.0, 15.0},
                   Point_3D{91.0, -21.0,  0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Above__R_Below)
{
    Triangle tr_1 {Point_3D{ 44.0,  55.0,   0.0},
                   Point_3D{-13.0,  42.0,  12.0},
                   Point_3D{ 66.0, -74.0, -33.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_On__R_Above)
{
    Triangle tr_1 {Point_3D{ 31.0, -26.0,  0.0},
                   Point_3D{ 83.0, -38.0,  0.0},
                   Point_3D{-22.0,  74.0, 37.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_On__R_Below)
{
    Triangle tr_1 {Point_3D{ 41.0, -62.0,   0.0},
                   Point_3D{-59.0,  41.0,   0.0},
                   Point_3D{ 73.0,  26.0, -29.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Below__R_Above)
{
    Triangle tr_1 {Point_3D{ 37.0,  20.0,   0.0},
                   Point_3D{-12.0,  77.0, -49.0},
                   Point_3D{ 40.0, -31.0,  16.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Below__R_On)
{
    Triangle tr_1 {Point_3D{76.0, -38.0,   0.0},
                   Point_3D{92.0,  17.0, -50.0},
                   Point_3D{ 5.0,  -6.0,   0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triagle, P_On__Q_Below__R_Below)
{
    Triangle tr_1 {Point_3D{24.0, -53.0,   0.0},
                   Point_3D{10.0,  35.0, -23.0},
                   Point_3D{73.0, -27.0, -61.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// P_loc == Loc_3D::Below
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST (Transform_Triangle, P_Below__Q_Above__R_Above)
{
    Triangle tr_1 {Point_3D{14.0, -63.0, -39.0},
                   Point_3D{95.0,  88.0,  18.0},
                   Point_3D{ 2.0,   8.0,   1.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Above__R_On)
{
    Triangle tr_1 {Point_3D{67.0, -32.0, -56.0},
                   Point_3D{ 0.0, -14.0,  26.0},
                   Point_3D{19.0, -21.0,   0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Above__R_Below)
{
    Triangle tr_1 {Point_3D{ 64.0, -24.0, -23.0},
                   Point_3D{ 11.0,  15.0,  55.0},
                   Point_3D{-83.0,  43.0, -73.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_On__R_Above)
{
    Triangle tr_1 {Point_3D{ 13.0,  53.0, -56.0},
                   Point_3D{-94.0,  26.0,   0.0},
                   Point_3D{ 82.0, -74.0,  81.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_On__R_On)
{
    Triangle tr_1 {Point_3D{ 23.0, 74.0, -59.0},
                   Point_3D{-25.0, 63.0,   0.0},
                   Point_3D{-86.0, 61.0,   0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 = tr_1;
    Triangle new_tr_2 {tr_2.P(), tr_2.R(), tr_2.Q()};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_On__R_Below)
{
    Triangle tr_1 {Point_3D{ 24.0,  60.0, -73.0},
                   Point_3D{ 34.0, -73.0,   0.0},
                   Point_3D{-92.0,  10.0, -20.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.Q(), tr_1.R(), tr_1.P()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Below__R_Above)
{
    Triangle tr_1 {Point_3D{61.0, 93.0, -27.0},
                   Point_3D{14.0, 25.0, -80.0},
                   Point_3D{ 7.0, -2.0,  23.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Below__R_On)
{
    Triangle tr_1 {Point_3D{75.0, 12.0, -27.0},
                   Point_3D{-9.0, 32.0, -80.0},
                   Point_3D{75.0, -1.0,   0.0}};

    Triangle tr_2 {Point_3D{1.0, 0.0, 0.0},
                   Point_3D{0.0, 1.0, 0.0},
                   Point_3D{0.0, 0.0, 0.0}};

    Triangle new_tr_1 {tr_1.R(), tr_1.P(), tr_1.Q()};
    Triangle new_tr_2 = tr_2;

    COMMON_PART;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
