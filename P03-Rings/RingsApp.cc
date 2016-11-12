#include "RingsApp.h"
#include "Maths.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <tuple>


std::vector<std::pair<float, float>> coeffs {
    {1.0f, 1.0f},
    {-1.0f, 1.0f},
    {-1.0f, -1.0f},
    {1.0f, -1.0f}
};


RingsApp::RingsApp(int majorVersion, int minorVersion, int depthBufferSize)
: GLApp(majorVersion, minorVersion, depthBufferSize)
, torus_(120, 120)
, camera_({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, &panningController_)
{  
    glClearColor(0.0f, 0.25f, 0.35f, 1.0f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

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
        Ring({ 1.0f,  1.0f}, {0.5f, 0.0f, 0.0f, 1.0f}, 15000.0f), 
        Ring({ 1.0f,  3.0f}, {0.0f, 0.5f, 0.0f, 1.0f},  3000.0f), 
        Ring({ 1.0f,  5.0f}, {0.0f, 0.0f, 0.5f, 1.0f},  4000.0f), 
        Ring({ 1.0f,  7.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, 10000.0f), 
        Ring({ 1.0f,  9.0f}, {0.5f, 0.0f, 0.5f, 1.0f},  5000.0f), 
        Ring({ 3.0f,  1.0f}, {0.0f, 0.5f, 0.5f, 1.0f},  2000.0f), 
        Ring({ 3.0f,  3.0f}, {0.5f, 0.5f, 0.5f, 1.0f},  6000.0f), 
        Ring({ 3.0f,  5.0f}, {0.5f, 0.0f, 0.0f, 1.0f},  1000.0f), 
        Ring({ 3.0f,  7.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, 12000.0f), 
        Ring({ 3.0f,  9.0f}, {0.0f, 0.0f, 0.5f, 1.0f}, 24000.0f), 
        Ring({ 5.0f,  1.0f}, {0.5f, 0.5f, 0.0f, 1.0f},  5000.0f), 
        Ring({ 5.0f,  3.0f}, {0.5f, 0.0f, 0.5f, 1.0f}, 14000.0f), 
        Ring({ 5.0f,  5.0f}, {0.0f, 0.5f, 0.5f, 1.0f},  5000.0f), 
        Ring({ 5.0f,  7.0f}, {0.5f, 0.5f, 0.5f, 1.0f},  4000.0f), 
        Ring({ 5.0f,  9.0f}, {0.5f, 0.0f, 0.0f, 1.0f},  7000.0f), 
        Ring({ 7.0f,  1.0f}, {0.0f, 0.5f, 0.0f, 1.0f},   500.0f), 
        Ring({ 7.0f,  3.0f}, {0.0f, 0.0f, 0.5f, 1.0f}, 12000.0f), 
        Ring({ 7.0f,  5.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, 12000.0f), 
        Ring({ 7.0f,  7.0f}, {0.5f, 0.0f, 0.5f, 1.0f}, 16000.0f), 
        Ring({ 7.0f,  9.0f}, {0.0f, 0.5f, 0.5f, 1.0f},  4000.0f), 
        Ring({ 9.0f,  1.0f}, {0.5f, 0.5f, 0.5f, 1.0f},  7000.0f), 
        Ring({ 9.0f,  3.0f}, {0.5f, 0.0f, 0.0f, 1.0f}, 17000.0f), 
        Ring({ 9.0f,  5.0f}, {0.0f, 0.5f, 0.5f, 1.0f},  5000.0f), 
        Ring({ 9.0f,  7.0f}, {0.5f, 0.5f, 0.5f, 1.0f}, 12000.0f), 
        Ring({ 9.0f,  9.0f}, {0.5f, 0.0f, 0.0f, 1.0f},  4000.0f), 
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
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(camera_.cameraSpaceTransform()));

    // Model transform
    for (auto const &coeffPair : coeffs) {
        for (auto const &ring : rings_) {
            glPushMatrix();
            glTranslatef(coeffPair.first * ring.position().x, 0.0f, coeffPair.second * ring.position().z);
            glRotatef(ring.currentAngle(), 0.0f, 1.0f, 0.0f);
            glScalef(0.5f, 0.5f, 0.5f);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)(&ring.color()));
            torus_.draw();
            glPopMatrix();
        }
    }

    glPopMatrix();
}


void RingsApp::resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, float(width) / height, 0.5f, 25.0f);
    glViewport(0, 0, width, height);
}


void RingsApp::handleEvent(SDL_Event &appEvent)
{
    SDL_PollEvent(&appEvent);

    float distance = 0.02f;

    if (appEvent.type == SDL_KEYDOWN) {
        switch(appEvent.key.keysym.sym) {
        case SDLK_RIGHT:
            camera_.moveRight(distance);
            break;
        case SDLK_LEFT:
            camera_.moveLeft(distance);
            break;
        case SDLK_UP:
            camera_.moveUp(distance);
            break;
        case SDLK_DOWN:
            camera_.moveDown(distance);
            break;

        // Rotation mode
        case SDLK_r:
            camera_.setController(&rotatingController_);
            break;
        case SDLK_p:
            camera_.setController(&panningController_);
            break;

        // Wireframe or Polygon
        case SDLK_l:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case SDLK_t:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
            break;
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
