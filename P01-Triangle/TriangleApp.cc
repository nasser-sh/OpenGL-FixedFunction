#include "TriangleApp.h"
#include <GL/gl.h>


TriangleApp::TriangleApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
{  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void TriangleApp::update(float millisElapsed)
{ }


void TriangleApp::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glVertex2f( 0.5f, -0.5f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f( 0.0f,  0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
    glEnd();
}


void TriangleApp::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}


void TriangleApp::handleEvent(SDL_Event &appEvent)
{
    SDL_WaitEvent(&appEvent);
}


bool TriangleApp::shouldQuit(SDL_Event const &appEvent)
{
    return appEvent.type == SDL_KEYDOWN;
}


TriangleApp::~TriangleApp()
{ }


int main()
{
    TriangleApp app(1, 1);
    app.start();
}
