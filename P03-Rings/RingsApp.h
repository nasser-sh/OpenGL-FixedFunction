#ifndef ROTATING_QUAD_APP_H
#define ROTATING_QUAD_APP_H


#include <GL/gl.h>
#include "GLApp.h"
#include "UnitTorus.h"


class RingsApp : public GLApp
{
public:
    RingsApp(int majorVersion, int minorVersion, int depthBufferSize = 24);
    ~RingsApp();
    
    void update(float millisElapsed) override;
    void draw() override;
    void resize(int width, int height) override;
    void handleEvent(SDL_Event &appEvent) override;
    bool shouldQuit(SDL_Event const &appEvent) override;

private:
    UnitTorus torus_;
    float currentTorusAngle_;
};

#endif // ROTATING_QUAD_APP_H
