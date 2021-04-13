#include "pch.h"
#include "Application.h"
#include "Core/Logger.h"
#include "Scene/Scene.h"

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
        if (!mWindow.ConstructWindow())
        {
            XN_CORE_ERROR("Failed to construct window.");

            return;
        }

        mRenderer.Init();
        mTime.Init();

        OnRun();

        if (SceneManager::sScenes.empty())
            SceneManager::AddScene("New Scene");
        if (!SceneManager::GetActiveScene())
            SceneManager::LoadScene(0);

        mIsRunning = true;

        while (mIsRunning)
        {
            PollEvents();
            Awake();
            Start();
            Update();
            Render();

            mWindow.Display();
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
        case SDL_WINDOWEVENT:
            mWindow.ProcessEvents(mEvent);
            break;
        case SDL_QUIT:
            OnExit();
            break;
        default:
            break;
        }
    }
}

void Xeno::Application::OnRun()
{ }

void Xeno::Application::OnUpdate()
{ }

void Xeno::Application::Awake()
{
    mSceneManager.Awake();
}

void Xeno::Application::Start()
{
    mSceneManager.Start();
}

void Xeno::Application::Update()
{
    OnUpdate();

    mTime.Update();
    mSceneManager.Update();
    mInput.Update();
    mSceneManager.ProcessRemovals();
}

void Xeno::Application::Render() const
{
    mSceneManager.Render();
    mRenderer.Render();
}

void Xeno::Application::OnExit()
{
    mSceneManager.OnExit();
    mIsRunning = false;
}
