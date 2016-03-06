#ifndef RING_H
#define RING_H


#include <GL/gl.h>


struct Position
{
    GLfloat x;
    GLfloat z;
};


struct Color
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
};


class Ring
{
public:
    Ring(Position const &position, Color const &color, float period);
    
    void updateRotation(float millisElapsed);

    Position const &position() const;
    Color const &color() const;
    float currentAngle() const;

private:
    Position position_;
    Color    color_;
    float    period_;
    float    currentAngle_;
};


#endif // RING_H