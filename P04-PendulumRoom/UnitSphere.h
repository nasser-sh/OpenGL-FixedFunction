#ifndef UNIT_SPHERE_H
#define UNIT_SPHERE_H


#include <cmath>
#include <vector>
#include <GL/gl.h>
#include "Vector3D.h"


/** \brief Store sphere mesh information.
 *
 *  Adapted from OpenGL Red Book 2nd Ed 
 */
class UnitSphere
{
public:
    UnitSphere(int subdivisionDepth);

    /** \brief Set the subdivisions of the sphere along its longitude and latitude
     *
     */
    void setLevelOfDetail(int subdivisionDepth);
    void draw() const;

private:
    static std::vector<Vector3D> vertexData;
    static int triangleIndices[20][3];

    void subdivide(Vector3D const &point1, Vector3D const &point2, Vector3D const &point3, int depth);
    void appendTriangleVertices(Vector3D const &point1, Vector3D const &point2, Vector3D const &point3);

    std::vector<Vector3D> attributes_;
};


#endif // UNIT_SPHERE_H