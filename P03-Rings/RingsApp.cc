#include "RingsApp.h"
#include <GL/gl.h>


RingsApp::RingsApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, torus_(60, 60)
, currentTorusAngle_(0.0f)
{  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


void RingsApp::update(float millisElapsed)
{  
    currentTorusAngle_ += millisElapsed / 15000.0f * 360.0f; 
}


void RingsApp::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(currentTorusAngle_, 0.0f, 1.0f, 0.0f);
    torus_.draw();
    glPopMatrix();
}


void RingsApp::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}


void RingsApp::handleEvent(SDL_Event &appEvent)
{
    SDL_PollEvent(&appEvent);
}


bool RingsApp::shouldQuit(SDL_Event const &appEvent)
{
    return appEvent.type == SDL_KEYDOWN && appEvent.key.keysym.sym == SDLK_ESCAPE;
}


RingsApp::~RingsApp()
{ }


int main()
{
    RingsApp app(1, 1);
    app.start();
}
