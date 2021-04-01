#include "pch.h"
#include "Application.h"

#include <glad.h>

Xeno::Application::Application(std::string name) :
    mAppName(std::move(name)),
    mWindow(WindowProperties
            { 
                mAppName, 
                SDL_WINDOWPOS_CENTERED, 
                SDL_WINDOWPOS_CENTERED, 
                SDL_WINDOW_OPENGL 
            })
{ }

Xeno::Application::~Application()
{
    SDL_Quit();
}

void Xeno::Application::Run()
{
    if (!mIsRunning)
    {
        mIsRunning = true;

        while (mIsRunning)
        {
            PollEvents();

            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            SDL_GL_SwapWindow(mWindow.mWindow);
        }
    }
}

void Xeno::Application::PollEvents()
{
    while (SDL_PollEvent(&mEvent))
    {
        switch (mEvent.type)
        {
        case SDL_QUIT:
            OnExit();
            break;
        default:
            break;
        }
    }
}

void Xeno::Application::OnExit()
{
    mIsRunning = false;
}
