#include "Maths.h"
#include "UnitSphere.h"


#define X 0.525731112119133696f
#define Z 0.850650808352039932f


std::vector<Vector3D> UnitSphere::vertexData {
    {-X, 0.0f, Z}, {X, 0.0f, Z}, {-X, 0.0f, -Z}, {X, 0.0f, -Z},
    {0.0f, Z, X}, {0.0f, Z, -X}, {0.0f, -Z, X}, {0.0f, -Z, -X},
    {Z, X, 0.0f}, {-Z, X, 0.0f}, {Z, -X, 0.0f}, {-Z, -X, 0.0f}
};


int UnitSphere::triangleIndices[20][3] = {
    { 1,  4, 0}, { 4, 9, 0}, {4,  5, 9}, {8, 5,  4}, { 1, 8, 4},
    { 1, 10, 8}, {10, 3, 8}, {8,  3, 5}, {3, 2,  5}, { 3, 7, 2},
    { 3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, { 6, 1, 0},
    {10,  1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2,  9}, {11, 2, 7}
};


UnitSphere::UnitSphere(int subdivisionDepth)
{
    if (subdivisionDepth > 6) {
        subdivisionDepth = 6;
    }

    setLevelOfDetail(subdivisionDepth);
}


void UnitSphere::setLevelOfDetail(int subdivisionDepth)
{
    attributes_.clear();

    for (int i = 0; i < 20; ++i) {
        subdivide(
            vertexData[triangleIndices[i][0]],
            vertexData[triangleIndices[i][1]],
            vertexData[triangleIndices[i][2]],
            subdivisionDepth);
    }
}


void UnitSphere::appendTriangleVertices(Vector3D const &point1, Vector3D const &point2, Vector3D const &point3)
{
    attributes_.push_back(point1);
    attributes_.push_back(point2);
    attributes_.push_back(point3);
}


void UnitSphere::subdivide(Vector3D const &point1, Vector3D const &point2, Vector3D const &point3, int depth)
{
    Vector3D point12, point23, point31;

    if (depth == 0) {
        appendTriangleVertices(point1, point2, point3);
        return;
    }

    /* calculate midpoints of each side */
    point12 = (point1 + point2) * 0.5f;
    point23 = (point2 + point3) * 0.5f;
    point31 = (point3 + point1) * 0.5f;


    /* extrude midpoints to lie on unit sphere */
    point12.normalize();
    point23.normalize();
    point31.normalize();

    /* recursively subdivide new triangles */
    subdivide(point1 , point12, point31, depth - 1);
    subdivide(point2 , point23, point12, depth - 1);
    subdivide(point3 , point31, point23, depth - 1);
    subdivide(point12, point23, point31, depth - 1);
}


void UnitSphere::draw() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &attributes_[0]);
    glNormalPointer(GL_FLOAT, 0, &attributes_[0]);

    glDrawArrays(GL_TRIANGLES, 0, attributes_.size());
}