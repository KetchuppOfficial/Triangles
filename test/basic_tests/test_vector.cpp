#include "vector.hpp"
#include "double_comparison.hpp"

#include <gtest/gtest.h>

using namespace Geom_Objects;

TEST (Vectors, Equality)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector vec_3 {1.000001, 2.000002, 3.000003};

    EXPECT_TRUE (vec_1 == vec_1);

    EXPECT_FALSE (vec_1 == vec_2);
    EXPECT_FALSE (vec_2 == vec_1);

    EXPECT_TRUE (vec_1 == vec_3);
    EXPECT_TRUE (vec_3 == vec_1);
}

TEST (Vectors, Inequality)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector vec_3 {1.000001, 2.000002, 3.000003};

    EXPECT_FALSE (vec_1 != vec_1);

    EXPECT_TRUE (vec_1 != vec_2);
    EXPECT_TRUE (vec_2 != vec_1);

    EXPECT_FALSE (vec_1 != vec_3);
    EXPECT_FALSE (vec_3 != vec_1);
}

TEST (Vectors, Addition)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector vec_3 {3.0, 4.0, 5.0};
    Vector null  {};

    EXPECT_TRUE (vec_1 + vec_2 == vec_2 + vec_1);
    EXPECT_TRUE ((vec_1 + vec_2) + vec_3 == vec_1 + (vec_2 + vec_3));
    EXPECT_TRUE (vec_1 + (-vec_1) == null);
    EXPECT_TRUE (vec_1 + null == vec_1);

    EXPECT_TRUE ((vec_1 + vec_2 == Vector {3.0, 5.0, 7.0}));

    /* Edge case: two vectors are approximately opposite *
     *            but their sum doesn't belong to        *
     *            epsilon-neighborhood of 0.0            */
    Vector big_ass_vec_1 = Vector{100000000.0};
    Vector big_ass_vec_2 = Vector{-100000001.0};
    EXPECT_TRUE (big_ass_vec_1 + big_ass_vec_2 == null);
}

TEST (Vectors, Subtraction)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector null {};

    EXPECT_FALSE (vec_1 - vec_2 == vec_2 - vec_1);

    EXPECT_TRUE ((vec_1 - vec_2 == Vector {-1.0, -1.0, -1.0}));
    EXPECT_TRUE ((vec_2 - vec_1 == Vector {1.0, 1.0, 1.0}));

    /* Edge case: two vectors are approximately equal *
     *            but their difference doesn't belong *
     *            to epsilon-neighborhood of 0.0      */
    Vector big_ass_vec_1 = Vector{100000000.0};
    Vector big_ass_vec_2 = Vector{100000001.0};
    EXPECT_TRUE (big_ass_vec_1 - big_ass_vec_2 == null);
}

TEST (Vectors, Multiplication)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector null  {};
    const double num_1 = 4.0;
    const double num_2 = 5.0;

    EXPECT_TRUE (vec_1 * num_1 == num_1 * vec_1);

    EXPECT_TRUE (num_1 * (num_2 * vec_1) == (num_1 * num_2) * vec_1);
    EXPECT_TRUE (1.0 * vec_1 == vec_1);
    EXPECT_TRUE ((num_1 + num_2) * vec_1 == num_1 * vec_1 + num_2 * vec_1);
    EXPECT_TRUE (num_1 * (vec_1 + vec_2) == num_1 * vec_1 + num_1 * vec_2);

    EXPECT_TRUE (vec_1 * 0.0 == null);
    EXPECT_TRUE (num_1 * null == null);

    EXPECT_TRUE ((-num_1) * vec_1 == num_1 * (-vec_1));
}

TEST (Vectors, Inversion)
{
    Vector vec {1.0, 2.0, 3.0};

    EXPECT_TRUE ((-vec == Vector{-1.0, -2.0, -3.0}));
    EXPECT_TRUE (-vec == -1.0 * vec);

    EXPECT_TRUE (-(-vec) == vec);
}

TEST (Vectors, Module)
{
    Vector null {};
    EXPECT_TRUE (cmp::are_equal (null.module (), 0.0));

    Vector vec_1 {1.0, 2.0, 3.0};
    EXPECT_TRUE (cmp::are_equal (vec_1.module (), 3.74165738));

    Vector vec_2 {1.0, 1.0, 1.0};
    EXPECT_TRUE (cmp::are_equal (vec_2.module (), 1.73205081));

    double big_ass_number = 1563413432.2;
    Vector vec_3 {1.0, 1.0, big_ass_number};
    EXPECT_TRUE (cmp::are_equal (vec_3.module (), big_ass_number));

    Vector vec_4 {-2.0, -3.0, 6.0};
    EXPECT_TRUE (cmp::are_equal (vec_4.module (), 7.0));

    Vector vec_5 {12.0, 16.0, 21.0};
    EXPECT_TRUE (cmp::are_equal (vec_5.module (), 29.0));
}

TEST (Vectors, Is_Zero)
{
    Vector null {};
    EXPECT_TRUE (null.is_zero ());

    Vector approx_null {-0.00000001, 0.0000009, 0.000000000008};
    EXPECT_TRUE (approx_null.is_zero ());

    Vector non_null {24.356, 72.4517, -32256574.1};
    EXPECT_FALSE (non_null.is_zero ());
}

TEST (Vectors, Scalar_Product)
{
    Vector vec_1 {39840329.2, -24532.895, 8734.12353};
    Vector vec_2 {-13767891.3, 12653.09862, 34912749.1233};
    EXPECT_DOUBLE_EQ (scalar_product (vec_1, vec_2), scalar_product (vec_2, vec_1));

    Vector vec_3 {1.0, 0.0, 4.0};
    Vector vec_4 {0.0, -6.0, 0.0};
    EXPECT_TRUE (cmp::are_equal (scalar_product (vec_3, vec_4), 0.0));

    Vector vec_5 {876325.1357, 79812.234412, -7671.122};
    Vector null {};
    EXPECT_TRUE (cmp::are_equal (scalar_product (vec_5, null), 0.0));

    Vector vec_6 {34.354, 1088.12, -882.0231};
    Vector vec_7 {78989.0, -414.177, 972.13};
    EXPECT_TRUE (cmp::are_equal (scalar_product (vec_6, vec_7), 1'405'472));

    Vector vec_8 {6712.98213, -0.000014145, 72653.45};
    Vector vec_9 {0.0000007862, -0.0000094781, 21.7532};
    EXPECT_TRUE (cmp::are_equal (scalar_product (vec_8, vec_9), 1'580'445));

    // Edge cases: two vectors are orthogonal
    Vector vec_10 {8583.23098, 14712.30};
    Vector vec_11 {22500.0 * 14712.30, -8583.23098 * 22500.0};
    EXPECT_TRUE (cmp::are_equal (scalar_product (vec_10, vec_11), 0.0));

    Vector vec_12 {12840854.3457, 78648714912.235};
    Vector vec_13 {78648714912.235 * 0.000006, -12840854.3457 * 0.000006};
    EXPECT_TRUE (cmp::are_equal (scalar_product (vec_12, vec_13), 0.0));
}

TEST (Vectors, Vector_Product)
{
    Vector e_1 {1.0, 0.0, 0.0};
    Vector e_2 {0.0, 1.0, 0.0};
    Vector e_3 {0.0, 0.0, 1.0};
    EXPECT_TRUE (vector_product (e_1, e_2) == e_3);
    EXPECT_TRUE (vector_product (e_1, e_3) == -e_2);
    EXPECT_TRUE (vector_product (e_2, e_3) == e_1);

    // Edge cases: two vectors are collinear
    Vector vec_1 {125390.241, 398124.14, 0.14122};
    EXPECT_TRUE (vector_product (vec_1, vec_1 * 22500.0).is_zero ());

    Vector vec_2 {77147807365.8579, 0.000000000135423515, 15937489.65824};
    EXPECT_TRUE (vector_product (vec_2, vec_2 * -0.000000872364).is_zero ());
}

TEST (Vectors, Triple_Product)
{
    Vector e_1 {1.0, 0.0, 0.0};
    Vector e_2 {0.0, 1.0, 0.0};
    Vector e_3 {0.0, 0.0, 1.0};
    EXPECT_TRUE (cmp::are_equal (triple_product (e_1, e_2, e_3), 1.0));
    EXPECT_TRUE (cmp::are_equal (triple_product (e_2, e_1, e_3), -1.0));
    EXPECT_TRUE (cmp::are_equal (triple_product (e_1, e_3, e_2), -1.0));
    EXPECT_TRUE (cmp::are_equal (triple_product (e_3, e_2, e_1), -1.0));
    EXPECT_TRUE (cmp::are_equal (triple_product (e_2, e_3, e_1), 1.0));
    EXPECT_TRUE (cmp::are_equal (triple_product (e_3, e_1, e_2), 1.0));

    Vector vec_1 {2891.928755, 892735.18, -0.000000315492};
    Vector vec_2 {10934.0182, -37813.34781, 12637893.2364};
    Vector vec_3 {0.00000038741, 0.000000002414135, 0.000357175};
    EXPECT_TRUE (cmp::are_equal (triple_product (vec_1, vec_2, vec_3), 845275.7));

    Vector vec_4 {76124.87529, 0.000082749, 1263582.59};
    Vector vec_5 {-937491.419, -0.0000007264, 0.00011214};
    Vector vec_6 {64783191.971, -0.000021412, 3.1415926535};
    EXPECT_TRUE (cmp::are_equal (triple_product (vec_4, vec_5, vec_6), 84827167.6));

    double k_1 {7149.870};
    double k_2 {-0.0000000327561};
    Vector vec_7 {1234.5, 6789.0, -38732.54};
    Vector vec_8 {2874.12, -12648.9871, 0.0000067821};
    Vector vec_9 {k_1 * vec_7.x_ + k_2 * vec_8.x_,
                  k_1 * vec_7.y_ + k_2 * vec_8.y_,
                  k_1 * vec_7.z_ + k_2 * vec_8.z_};
    EXPECT_TRUE (cmp::are_equal (triple_product (vec_7, vec_8, vec_9), 0.0));
}

TEST (Vectors, Are_Collinear)
{
    Vector vec_1 {32802.0, 81749.8721, -0.00000065271210841};
    Vector null {};
    EXPECT_TRUE (are_collinear (vec_1, 172684.187239 * vec_1));
    EXPECT_TRUE (are_collinear (vec_1, 0.00000000038742 * vec_1));
    EXPECT_TRUE (are_collinear (vec_1, null));

    Vector vec_2 {-897461.56547175, 7.761208, -0.000000000000172564890};
    Vector vec_3 {vec_2.x_, vec_2.y_, vec_2.z_ + 1};
    EXPECT_FALSE (are_collinear (vec_2, vec_3));
}

TEST (Vectors, Are_Orthogonal)
{
    Vector vec_1 {0.0002467197, 6570082.97240, -0.37813};
    Vector vec_2 {1 / vec_1.x_, 1 / vec_1.y_, -2 / vec_1.z_};
    Vector null {};
    EXPECT_TRUE (are_orthogonal (vec_1, vec_2));
    EXPECT_TRUE (are_orthogonal (vec_1, null));

    Vector vec_3 {8279.249, 1.0074197, -718.24678};
    Vector vec_4 {0.0000274814, 0.019238764, -0.279};
    EXPECT_FALSE (are_orthogonal (vec_3, vec_4));
}

TEST (Vectors, Are_Coplanar)
{
    double k_1 {6736.8};
    double k_2 {-0.32};
    Vector vec_1 {78364.03174581, -0.018264, 46247124152.78};
    Vector vec_2 {6742.761, 0.1, -267545.53};
    Vector vec_3 {k_1 * vec_1.x_ + k_2 * vec_2.x_,
                  k_1 * vec_1.y_ + k_2 * vec_2.y_,
                  k_1 * vec_1.z_ + k_2 * vec_2.z_};
    Vector null {};
    EXPECT_TRUE (are_coplanar (vec_1, vec_2, vec_3));
    EXPECT_TRUE (are_coplanar (vec_1, vec_2, null));
    EXPECT_TRUE (are_coplanar (vec_1, null, vec_3));
    EXPECT_TRUE (are_coplanar (null, vec_2, vec_3));

    Vector e_1 {1.0, 0.0, 0.0};
    Vector e_2 {0.0, 1.0, 0.0};
    Vector e_3 {0.0, 0.0, 1.0};
    EXPECT_FALSE (are_coplanar (e_1, e_2, e_3));  
}

TEST (Vectors, Ctor_From_Points)
{
    // Edge case: constructing vector from 2 approximately matching points
    Point big_ass_pt_1 {100000001};
    Point big_ass_pt_2 {100000000};
    Vector vec {big_ass_pt_1, big_ass_pt_2};
    Vector null {};
    EXPECT_TRUE (vec == null);
}
