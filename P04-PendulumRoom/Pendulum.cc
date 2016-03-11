#include "Pendulum.h"
#include "Maths.h"
#include <cmath>


/** The equations of motion referenced in this implementation are not entirely
 *  accurate, because they are based on the small angle assumption. However, they
 *  are good enough for this simulation
 */


Pendulum::Pendulum(Vector3D const &position, float radius, float amplitude)
: bobMesh_(4)
, position_(position)
, timeStamp_(0.0f)
, radius_(radius)
, amplitude_(radians(amplitude))
{ 
    naturalPeriod_ = twoPi() * std::sqrt(radius_ / g());
}


Vector3D const &Pendulum::position() const
{
    return position_;
}


void Pendulum::update(float millisElapsed)
{
    timeStamp_ = std::fmod(timeStamp_ + millisElapsed, naturalPeriod_);
}


GLfloat Pendulum::currentAngle() const
{
    return amplitude_ * std::cos(twoPi() / naturalPeriod_ * timeStamp_);
}


void Pendulum::draw() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(position_.x, position_.y, position_.z);
    glRotatef(degrees(currentAngle()), 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -radius_, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);
    bobMesh_.draw();
    glPopMatrix();
}