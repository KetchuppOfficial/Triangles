#ifndef TEST_INCLUDE_ALGORITHM_TESTING_HPP
#define TEST_INCLUDE_ALGORITHM_TESTING_HPP

#include "triangle.hpp"

namespace Geom_Objects
{

void space_transformation (Triangle &tr_1, Triangle &tr_2);
void transform_triangle (Triangle &tr_1, const Loc_3D P1_loc, const Loc_3D Q1_loc,
                         const Loc_3D R1_loc, Triangle &tr_2);
}

#endif // TEST_INCLUDE_ALGORITHM_TESTING_HPP
