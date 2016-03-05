#include "RotatingQuadApp.h"
#include <GL/gl.h>


// from: http://www.codeproject.com/Articles/23444/A-Simple-OpenGL-Stipple-Polygon-Example-EP-OpenGL
GLubyte fly[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
    0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
    0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
    0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
    0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
    0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
    0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
    0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
    0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
    0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
    0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};



RotatingQuadApp::RotatingQuadApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, primitive_(GL_QUADS)
, currentAngle_(0.0f)
, isMoving_(true)
{  
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(4.0f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(fly);
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
        glVertex2f(-0.5f, -0.5f);
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
