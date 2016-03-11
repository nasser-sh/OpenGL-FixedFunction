#include "PendulumRoomApp.h"
#include <GL/gl.h>
#include <GL/glu.h>


PendulumRoomApp::PendulumRoomApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, pendulum_(Vector3D(0.0f, 3.0f, -10.0f), 0.5f, 60.0f)
{ 
    glClearColor(0.0f, 0.25f, 0.35f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


void PendulumRoomApp::update(float millisElapsed)
{
    pendulum_.update(millisElapsed);
}


void PendulumRoomApp::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0f, 0.0f,  0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f,  0.0f);
    pendulum_.draw();
}


void PendulumRoomApp::resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, float(width) / height, 1.0f, 25.0f);
    glViewport(0, 0, width, height);
}


void PendulumRoomApp::handleEvent(SDL_Event &appEvent)
{
    SDL_PollEvent(&appEvent);
}


bool PendulumRoomApp::shouldQuit(SDL_Event const &appEvent)
{
    return appEvent.type == SDL_KEYDOWN && appEvent.key.keysym.sym == SDLK_ESCAPE;
}


PendulumRoomApp::~PendulumRoomApp()
{

}


int main()
{
    PendulumRoomApp app(1, 1);
    app.start();
}