#ifndef PENDULUM_H
#define PENDULUM_H


#include "Vector3D.h"
#include "UnitSphere.h"


class Pendulum
{
public:
    /** 
     *  @param position position of equilibrium point, in application units
     *  @param radius radius of rotation, in application units
     *  @param amplitude amplitude of vibration in degrees
     */
    Pendulum(Vector3D const &position, float radius, float amplitude);

    Vector3D const &position() const;
    void update(float millisElapsed);
    void draw() const;

private:    
    UnitSphere bobMesh_;
    Vector3D position_;

    float timeStamp_;
    float naturalPeriod_;
    float radius_;
    float amplitude_;
}; 


#endif // PENDULUM_H