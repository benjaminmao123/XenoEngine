#include "pch.h"
#include "Core/Application.h"
#include "Core/Logger.h"

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

std::string ParseFile(const std::string& path)
{
    std::ifstream ifs(path);

    if (!ifs.is_open())
    {
        XN_CORE_ERROR("Failed to open file: {0}", path);

        return std::string();
    }

    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    return content;
}

void Xeno::Application::Run()
{
    if (!mIsRunning)
    {
        Create();
        CameraComponent camera;
        camera.SetProjectionType(CameraComponent::ProjectionType::ORTHOGRAPHIC);
        TransformComponent transform;
        transform.SetScale(100, 100, transform.GetScale().z);

        while (mIsRunning)
        {
            mWindow.Clear(0, 0, 0, 255);

            PollEvents();
            Update();
            Renderer::DrawQuad(transform, camera, SDL_Color(255, 255, 255, 255));

            SDL_GL_SwapWindow(mWindow.mWindow);
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

    mRenderer.Init();

    OnCreate();

    mIsRunning = true;
}

void Xeno::Application::Update()
{
    mTime.Update();
    mInput.Update();
    OnUpdate();
}
