#ifndef TRIANGLE_APP_H
#define TRIANGLE_APP_H


#include "GLApp.h"
#include <GL/gl.h>


class TriangleApp : public GLApp
{
public:
    TriangleApp(int majorVersion, int minorVersion, int depthBufferSize = 24);
    ~TriangleApp();
    
    void update(float millisElapsed) override;
    void draw() override;
    void resize(int width, int height) override;
    void handleEvent(SDL_Event &appEvent) override;
    bool shouldQuit(SDL_Event const &appEvent) override;
};

#endif // TRIANGLE_APP_H
