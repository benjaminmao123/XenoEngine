#include "pch.h"
#include "Core/Application.h"
#include "Core/Logger.h"

#include <glad.h>
#include <SDL2/SDL.h>

Xeno::Application::Application(const Window::WindowProperties& props) :
    mWindow(props)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        XN_CORE_ERROR(SDL_GetError());

        throw std::runtime_error("SDL failed to initialize.");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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
        mInput.ProcessEvents(mEvent);

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
    mTime.Update();
    mInput.Update();
    OnUpdate();
    mWindow.Update();
}
