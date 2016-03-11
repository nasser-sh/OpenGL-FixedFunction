#ifndef PENDULUM_ROOM_H
#define PENDULUM_ROOM_H


#include "GLApp.h"
#include "Pendulum.h"
#include "Ball.h"


class PendulumRoomApp : public GLApp
{
public:
    PendulumRoomApp(int majorVersion, int minorVersion, int depthBufferSize = 24);
    ~PendulumRoomApp();
    
    void update(float millisElapsed) override;
    void draw() override;
    void resize(int width, int height) override;
    void handleEvent(SDL_Event &appEvent) override;
    bool shouldQuit(SDL_Event const &appEvent) override;

private:
    Pendulum pendulum_;
    Ball ball_;
};


#endif // PENDULUM_ROOM_H