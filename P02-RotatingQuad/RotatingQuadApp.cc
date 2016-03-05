#include "RotatingQuadApp.h"
#include <GL/gl.h>


RotatingQuadApp::RotatingQuadApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, primitive_(GL_QUADS)
, currentAngle_(0.0f)
, isMoving_(true)
{  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(4.0f);
}


void RotatingQuadApp::update(float millisElapsed)
{ 
    if (isMoving_) {
        currentAngle_ += millisElapsed / 15000.0f * 360.0f;
    }
}


void RotatingQuadApp::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(currentAngle_, 0.0f, 0.0f, 1.0f);

    glBegin(primitive_);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
        glVertex2f(-0.5f,- 0.5f);
    glEnd();
    
    glPopMatrix();
}


void RotatingQuadApp::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}


void RotatingQuadApp::handleEvent(SDL_Event &appEvent)
{
    SDL_PollEvent(&appEvent);
    
    if (appEvent.type == SDL_KEYDOWN) {
        switch(appEvent.key.keysym.sym) {
        case SDLK_SPACE:
            isMoving_ = !isMoving_;
            break;
        case SDLK_p:
            primitive_ = GL_POINTS;
            break;
        case SDLK_q:
            primitive_ = GL_QUADS;
            break;
        case SDLK_l:
            primitive_ = GL_LINE_LOOP;
            break;
        }
    }
}


bool RotatingQuadApp::shouldQuit(SDL_Event const &appEvent)
{
    return appEvent.type == SDL_KEYDOWN && appEvent.key.keysym.sym == SDLK_ESCAPE;
}


RotatingQuadApp::~RotatingQuadApp()
{ }


int main()
{
    RotatingQuadApp app(1, 1);
    app.start();
}
