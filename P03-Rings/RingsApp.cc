#include "RingsApp.h"
#include <GL/gl.h>
#include <GL/glu.h>


RingsApp::RingsApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, torus_(120, 120)
, currentTorusAngle_(0.0f)
{  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(90.0f, float(1280) / 960, 0.1f, 100.0f);
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
    
    // View transform
    gluLookAt(
        0.0f, 0.0f,  0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f,  0.0f);

    // Model transform
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(currentTorusAngle_, 0.0f, 1.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    
    torus_.draw();
    glPopMatrix();
}


void RingsApp::resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, float(width) / height, 0.1f, 200.0f);
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
