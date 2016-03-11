#include "Ball.h"



Ball::Ball(Vector3D const &position, float radius)
: sphere_(4)
, position_(position)
, radius_(radius)
{ }


void Ball::draw() const
{
    glPushMatrix();
    glTranslatef(position_.x, position_.y, position_.z);
    glScalef(radius_, radius_, radius_);
    
    GLfloat  materialEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat  materialDiffuse[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

    sphere_.draw();
    
    glPopMatrix();
}