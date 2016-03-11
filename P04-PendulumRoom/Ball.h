#ifndef BALL_H
#define BALL_H


#include "UnitSphere.h"
#include "Vector3D.h"


class Ball
{
public:
    Ball(Vector3D const &position, float radius);

    void draw() const;
    
private:
    UnitSphere sphere_;
    Vector3D position_;
    float radius_;
};


#endif // BALL_H