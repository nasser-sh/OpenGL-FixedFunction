#ifndef GLAPP_H
#define GLAPP_H


#include <chrono>
#include <SDL2/SDL.h>


class GLApp {
public:
    GLApp(int majorVersion, int minorVersion, int depthBufferSize = 24);
    virtual ~GLApp();

    virtual void update(float millisElapsed) = 0;
    virtual void draw() = 0;
    virtual void resize(int width, int height) = 0;
    virtual void handleEvent(SDL_Event &appEvent) = 0;
    virtual bool shouldQuit(SDL_Event const &appEvent) = 0;

    void start();

private:
    float millisElapsed();

    SDL_Window    *mainWindow_;
    SDL_GLContext  mainContext_;
    SDL_Event      appEvent_;

    std::chrono::high_resolution_clock::time_point currentTime_;
};


#endif // GLAPP_H
