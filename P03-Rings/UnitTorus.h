#ifndef TORUS_H
#define TORUS_H


#include <vector>
#include <GL/gl.h>


class UnitTorus
{
public:
    UnitTorus(int majorDivisionCount, int minorDivisionCount, float minorRadius = 0.2f);

    void setLevelOfDetail(int majorDivisions, int minorDivisions);
    void draw() const;

private:
    static constexpr float majorRadius_ = 1.0f;

    void setVertices(int majorDivisions, int minorDivisions);
    void setIndices(int majorDivisions, int minorDivisions);

    std::vector<GLfloat> attributes_;
    std::vector<GLushort> indices_;
    float minorRadius_;
};


#endif // TORUS_H