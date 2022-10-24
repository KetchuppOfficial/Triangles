#ifndef TEST_INCLUDE_ALGORITHM_TESTING_HPP
#define TEST_INCLUDE_ALGORITHM_TESTING_HPP

#include "triangle.hpp"

namespace Geom_Objects
{

bool intersection_in_2D (const Triangle &tr_1_, const Triangle &tr_2_);
inline Loc_2D magic_product (const Point &P, const Point &Q, const Point &M);
void space_transformation (Triangle &tr_1, Triangle &tr_2);
void transform_triangle (Triangle &tr_1, const Loc_3D P1_loc, const Loc_3D Q1_loc,
                         const Loc_3D R1_loc, Triangle &tr_2);
}

#endif // TEST_INCLUDE_ALGORITHM_TESTING_HPP
