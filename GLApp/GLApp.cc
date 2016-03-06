#include "GLApp.h"
#include <iostream>


void printSdlError()
{
    std::cerr << SDL_GetError() << '\n';
}


void initializeSdl(int majorVersion, int minorVersion, int depthBufferSize)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depthBufferSize);
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printSdlError();
    }
}


GLApp::GLApp(int majorVersion, int minorVersion, int depthBufferSize)
{
    initializeSdl(majorVersion, minorVersion, depthBufferSize);

    mainWindow_ = SDL_CreateWindow("Hello, GL!", 100, 100, 1280, 960,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(mainWindow_ == nullptr)
    {
        printSdlError();
    }

    mainContext_ = SDL_GL_CreateContext(mainWindow_);
    SDL_GL_SetSwapInterval(1);

    if(mainContext_ == nullptr)
    {
        printSdlError();
    }
    
    currentTime_ = std::chrono::high_resolution_clock::now();
}


void GLApp::start()
{
    resize(1280, 960);
    do {
        update(millisElapsed());
        draw();
        SDL_GL_SwapWindow(mainWindow_);
        handleEvent(appEvent_);
        if (appEvent_.type == SDL_WINDOWEVENT && appEvent_.window.event == SDL_WINDOWEVENT_RESIZED) {
            resize(appEvent_.window.data1, appEvent_.window.data2);
        }
    } while(!(shouldQuit(appEvent_) || appEvent_.type == SDL_QUIT));
}


float GLApp::millisElapsed()
{
    using namespace std::chrono;
    high_resolution_clock::time_point nextTime = high_resolution_clock::now();
    float elapsed = (float)duration_cast<milliseconds>(nextTime - currentTime_).count();
    currentTime_ = nextTime;
    return elapsed;
}


GLApp::~GLApp()
{
    SDL_GL_DeleteContext(mainContext_);
    SDL_DestroyWindow(mainWindow_);
    SDL_Quit();
}
