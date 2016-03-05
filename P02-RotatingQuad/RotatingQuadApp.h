#ifndef ROTATING_QUAD_APP_H
#define ROTATING_QUAD_APP_H


#include "GLApp.h"
#include <GL/gl.h>


class RotatingQuadApp : public GLApp
{
public:
    RotatingQuadApp(int majorVersion, int minorVersion, int depthBufferSize = 24);
    ~RotatingQuadApp();
    
    void update(float millisElapsed) override;
    void draw() override;
    void resize(int width, int height) override;
    void handleEvent(SDL_Event &appEvent) override;
    bool shouldQuit(SDL_Event const &appEvent) override;

private:
    GLenum primitive_;
    float currentAngle_;
    bool  isMoving_;
};

#endif // ROTATING_QUAD_APP_H
