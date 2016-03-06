#include "UnitTorus.h"
#include "Maths.h"
#include <cmath>


/** \brief Return circle vertices in its own model space, in YZ plane
 */
std::vector<GLfloat> circleVertices(int sideCount, float radius)
{
    std::vector<GLfloat> vertices;
    float anglePerSegment = twoPi() / float(sideCount);

    for (int side = 0; side < sideCount; ++side) {
        float currentAngle = anglePerSegment * float(side);
        vertices.push_back(0.0f);
        vertices.push_back(radius * std::sin(currentAngle));
        vertices.push_back(radius * std::cos(currentAngle));
    }

    return vertices;
}


UnitTorus::UnitTorus(int majorDivisionCount, int minorDivisionCount, float minorRadius)
: minorRadius_(minorRadius)
{ 
    setLevelOfDetail(majorDivisionCount, minorDivisionCount);
}


void UnitTorus::setLevelOfDetail(int majorDivisionCount, int minorDivisionCount)
{
    setVertices(majorDivisionCount, minorDivisionCount);
    setIndices(majorDivisionCount, minorDivisionCount);
}


void UnitTorus::setVertices(int majorDivisionCount, int minorDivisionCount)
{
    std::vector<GLfloat> minorCircleVertices = circleVertices(minorDivisionCount, minorRadius_);
    float anglePerDivision = twoPi() / majorDivisionCount;

    std::vector<GLfloat> attributes;
    std::vector<GLfloat> normals;

    for(int majorDivision = 0; majorDivision < majorDivisionCount; ++majorDivision) {
        float currentMajorAngle = anglePerDivision * float(majorDivision);
        float sinMajor = std::sin(currentMajorAngle);
        float cosMajor = std::cos(currentMajorAngle);

        float transformedOriginX = -majorRadius_ * sinMajor;
        float transformedOriginY =  majorRadius_ * cosMajor;
        float transformedOriginZ = 0.0f;

        for (int minorDivision = 0; minorDivision < minorDivisionCount; ++minorDivision) {
            //float modelSpaceX = minorCircleVertices[3 * minorDivision];
            float modelSpaceY = minorCircleVertices[3 * minorDivision + 1];
            float modelSpaceZ = minorCircleVertices[3 * minorDivision + 2];

            float transformedX = -modelSpaceY * sinMajor - majorRadius_ * sinMajor;
            float transformedY =  modelSpaceY * cosMajor + majorRadius_ * cosMajor;
            float transformedZ =  modelSpaceZ;

            // vertices
            attributes.push_back(transformedX);
            attributes.push_back(transformedY);
            attributes.push_back(transformedZ);

            // normals
            attributes.push_back((transformedX - transformedOriginX) / minorRadius_);
            attributes.push_back((transformedY - transformedOriginY) / minorRadius_);
            attributes.push_back((transformedZ - transformedOriginZ) / minorRadius_);
        }
    }

    attributes_ = std::move(attributes);
    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), &attributes_[0]);
    glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), &attributes_[3]);
}


void UnitTorus::setIndices(int majorDivisionCount, int minorDivisionCount)
{
    std::vector<GLushort> indices;

    for (int majorDivision = 0; majorDivision < majorDivisionCount - 1; ++majorDivision) {
        GLushort base = majorDivision * minorDivisionCount;

        for(int minorDivision = 0; minorDivision < minorDivisionCount; ++minorDivision) {
            indices.push_back(base + minorDivision);
            indices.push_back(base + minorDivisionCount + minorDivision);
        }

        // close off strip
        indices.push_back(base);
        indices.push_back(base + minorDivisionCount);
    }

    // last section
    for(int minorDivision = 0; minorDivision < minorDivisionCount; ++minorDivision) {
        indices.push_back(minorDivisionCount * (majorDivisionCount - 1) + minorDivision);
        indices.push_back(minorDivision);
    }

    indices.push_back(minorDivisionCount * (majorDivisionCount - 1));
    indices.push_back(0);
    indices_ = std::move(indices);
}


void UnitTorus::draw() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, &indices_[0]);
}
