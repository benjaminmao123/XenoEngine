#include "pch.h"
#include "Core/Application.h"
#include "Core/Logger.h"

#include <glad.h>
#include <SDL2/SDL.h>

Xeno::Application::Application(std::string name) :
    mAppName(std::move(name)),
    mWindow(WindowProperties{ mAppName, SDL_WINDOWPOS_CENTERED, 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOW_OPENGL })
{
    Logger::Init();
}

Xeno::Application::~Application()
{
    SDL_Quit();
}

void Xeno::Application::Run()
{
    if (!mIsRunning)
    {
        Create();

        while (mIsRunning)
        {
            mWindow.Clear(0, 0, 0, 255);
            
            PollEvents();
            Update();
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

void Xeno::Application::OnCreate()
{ }

void Xeno::Application::OnUpdate()
{ }

void Xeno::Application::Create()
{
    if (!mWindow.ConstructWindow())
    {
        XN_CORE_ERROR("Failed to construct window.");

        return;
    }

    OnCreate();

    mIsRunning = true;
}

void Xeno::Application::Update()
{
    OnUpdate();

    mWindow.Update();
}
