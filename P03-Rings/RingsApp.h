#ifndef ROTATING_QUAD_APP_H
#define ROTATING_QUAD_APP_H


#include <GL/gl.h>
#include <vector>
#include "GLApp.h"
#include "UnitTorus.h"
#include "Ring.h"


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
    float viewAngle_;
    UnitTorus torus_;
    std::vector<Ring> rings_;
};

#endif // ROTATING_QUAD_APP_H
