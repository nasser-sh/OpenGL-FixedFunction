#include "Pendulum.h"
#include "Maths.h"
#include <cmath>

/** The equations of motion referenced in this implementation are not entirely
 *  accurate, because they are based on the small angle assumption. However, they
 *  are good enough for this simulation
 */


Pendulum::Pendulum(Vector3D const &position, float radius, float amplitude)
: bobMesh_(4)
, timeStamp_(0.0f)
, radius_(radius)
, amplitude_(radians(amplitude))
{ 
    position_.x =  radius_ * std::sin(0.0f);
    position_.y = -radius_ * std::cos(0.0f);
    position_.z = position.z;

    naturalPeriod_ = twoPi() * std::sqrt(radius_ / g());
}


Vector3D const &Pendulum::position() const
{
    return position_;
}


void Pendulum::update(float millisElapsed)
{
    timeStamp_ = std::fmod(timeStamp_ + millisElapsed, naturalPeriod_);
    float currentAngle = amplitude_ * std::cos(twoPi() / naturalPeriod_ * timeStamp_);
    position_.x =  radius_ * std::sin(currentAngle);
    position_.y = -radius_ * std::cos(currentAngle);
}


void Pendulum::draw() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(position_.x, position_.y, position_.z);
    glScalef(0.5f, 0.5f, 0.5f);
    bobMesh_.draw();
    glPopMatrix();
}