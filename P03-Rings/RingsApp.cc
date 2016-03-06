#include "RingsApp.h"
#include "Maths.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>


RingsApp::RingsApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, torus_(120, 120)
, viewAngle_(0.0f)
{  
    glClearColor(0.0f, 0.25f, 0.35f, 1.0f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(
        0.0f, 0.0f,  0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f,  0.0f);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    GLfloat lightPosition[] = {0.0f, 3.0f, 0.0f, 1.0f};  
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    rings_ = std::vector<Ring> {
        Ring({ 0.0f, -2.0f}, {0.5f, 0.0f, 0.0f, 1.0f}, 15000.0f), 
        Ring({ 3.0f, -1.0f}, {0.0f, 0.5f, 0.0f, 1.0f},  5000.0f), 
        Ring({ 2.0f,  2.0f}, {0.0f, 0.0f, 0.5f, 1.0f},  3000.0f), 
        Ring({ 1.0f,  5.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, 12000.0f), 
        Ring({-2.0f,  1.0f}, {0.0f, 0.5f, 0.5f, 1.0f},  4000.0f), 
        Ring({-5.0f,  3.0f}, {0.5f, 0.0f, 0.5f, 1.0f},  8000.0f), 
    };
}


void RingsApp::update(float millisElapsed)
{  
    for (auto &ring : rings_) {
        ring.updateRotation(millisElapsed);
    } 
}


void RingsApp::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    // Model transform
    for (auto &ring : rings_) {
        glPushMatrix();
        glTranslatef(ring.position().x, 0.0f, ring.position().z);
        glRotatef(ring.currentAngle(), 0.0f, 1.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)(&ring.color()));
        torus_.draw();
        glPopMatrix();
    }
}


void RingsApp::resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, float(width) / height, 0.1f, 10.0f);
    glViewport(0, 0, width, height);
}


void RingsApp::handleEvent(SDL_Event &appEvent)
{
    SDL_PollEvent(&appEvent);

    if (appEvent.type == SDL_KEYDOWN) {
        bool  needsUpdate = false;
    
        switch(appEvent.key.keysym.sym) {
        case SDLK_RIGHT:
            needsUpdate = true;
            viewAngle_ = std::fmod(viewAngle_ + 0.02f, twoPi());
            break;
        case SDLK_LEFT:
            needsUpdate = true;
            viewAngle_ -= 0.02f;
            if (viewAngle_ < 0.0f) {
                viewAngle_ += twoPi();
            }
            break;
        }

        if (needsUpdate) {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(
                0.0f, 0.0f, 0.0f,
                std::sin(viewAngle_), 0.0f, -std::cos(viewAngle_),
                0.0f, 1.0f, 0.0f);
        }
    }
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
