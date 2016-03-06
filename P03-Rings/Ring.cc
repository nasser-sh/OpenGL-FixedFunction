#include "Ring.h"
#include <cmath>


Ring::Ring(Position const &position, Color const &color, float period)
: position_(position)
, color_(color)
, period_(period)
, currentAngle_(0.0f)
{ }


void Ring::updateRotation(float millisElapsed)
{
    currentAngle_ = std::fmod(currentAngle_ + millisElapsed / period_ * 360.0f, 360.0f);
}


Position const &Ring::position() const
{
    return position_;
}


Color const &Ring::color() const
{
    return color_;
}


float Ring::currentAngle() const
{
    return currentAngle_;
}