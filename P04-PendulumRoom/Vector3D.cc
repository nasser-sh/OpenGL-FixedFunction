#include "Vector3D.h"
#include <cmath>


Vector3D::Vector3D()
: x(0.0f)
, y(0.0f)
, z(0.0f)
{ }


Vector3D::Vector3D(float _x, float _y, float _z)
: x(_x)
, y(_y)
, z(_z) 
{ }


void Vector3D::normalize() 
{
    float magnitude = std::sqrt(x * x + y * y + z * z);

    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}


GLfloat &Vector3D::operator[](int index) 
{ 
    return *((GLfloat*)this + index); 
}


GLfloat Vector3D::operator[](int index) const
{
    return *((GLfloat*)this + index); 
}


Vector3D &Vector3D::operator*=(GLfloat scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


Vector3D &Vector3D::operator+=(Vector3D const &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}


Vector3D operator*(Vector3D vec, float scalar)
{
    return vec *= scalar;
}


Vector3D operator*(float scalar, Vector3D vec)
{
    return vec * scalar;
}


Vector3D operator+(Vector3D vec1, Vector3D const &vec2)
{
    return vec1 += vec2;
}