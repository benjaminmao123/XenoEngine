#include "pch.h"
#include "Application.h"
#include "Logger.h"

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
        if (!mWindow.ConstructWindow())
        {
            XN_CORE_ERROR("Failed to construct window.");

            return;
        }

        mIsRunning = true;

        while (mIsRunning)
        {
            PollEvents();

            mWindow.Clear(255, 0, 0, 255);
            mWindow.Update();
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
