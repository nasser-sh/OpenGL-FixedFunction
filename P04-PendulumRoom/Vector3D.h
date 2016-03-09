#ifndef VECTOR3D_H
#define VECTOR3D_H


#include <GL/gl.h>


class Vector3D
{
public:
    Vector3D();
    Vector3D(float _x, float _y, float _z);

    GLfloat  &operator[](int index);
    GLfloat   operator[](int index) const;
    Vector3D &operator*=(float scalar);
    Vector3D &operator+=(Vector3D const &other);

    void normalize();

    GLfloat x;
    GLfloat y;
    GLfloat z;
};


Vector3D operator*(Vector3D vec, float scalar);
Vector3D operator*(float scalar, Vector3D vec);
Vector3D operator+(Vector3D vec1, Vector3D const &vec2);

using Point3D = Vector3D;


#endif // VECTOR3D_H