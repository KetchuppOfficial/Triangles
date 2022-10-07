#include "vector.hpp"

namespace Geom_Objects
{

Vector operator+ (const Vector &lhs, const Vector &rhs)
{
    Vector sum = lhs;
    return (sum += rhs);
}

Vector operator- (const Vector &lhs, const Vector &rhs)
{
    Vector diff = lhs;
    return (diff -= rhs);
}

Vector operator* (const Vector &lhs, const double coeff)
{
    Vector product = lhs;
    return (product *= coeff);
}

double scalar_product (const Vector &lhs, const Vector &rhs)
{
    return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
}

Vector vector_product (const Vector &lhs, const Vector &rhs)
{
    return Vector {lhs.y_ * rhs.z_ - lhs.z_ * rhs.y_, lhs.x_ * rhs.z_ - lhs.z_ * rhs.x_,
                   lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_};
}

double triple_product (const Vector &first, const Vector &second, const Vector &third)
{
    return first.x_ * (second.y_ * third.z_ - second.z_ * third.y_) -
           first.y_ * (second.x_ * third.z_ - second.z_ * third.x_) +
           first.z_ * (second.x_ * third.y_ - second.y_ * third.x_);
}

bool are_equal (const Vector &lhs, const Vector &rhs)
{
    return (cmp::are_equal (lhs.x_, rhs.x_) && cmp::are_equal (lhs.y_, rhs.y_) &&
            cmp::are_equal (lhs.z_, rhs.z_));
}

bool are_collinear (const Vector &first, const Vector &second)
{
    return vector_product (first, second).is_zero ();
}

bool are_coplanar (const Vector &first, const Vector &second, const Vector &third)
{
    return cmp::are_equal (triple_product (first, second, third), 0.0);
}

} // namespace Geom_Objects
