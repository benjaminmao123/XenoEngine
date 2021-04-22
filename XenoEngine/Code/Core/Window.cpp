#include "pch.h"
#include "Window.h"
#include "Core/Logger.h"

#include <glad/glad.h>

Xeno::Window::Window(WindowProperties props) :
    mWindowProps(std::move(props))
{ }

Xeno::Window::~Window()
{
    SDL_DestroyWindow(mWindow);
}

bool Xeno::Window::ConstructWindow()
{
    if (mIsInitialized)
        return false;

    mWindow = SDL_CreateWindow(mWindowProps.mTitle.c_str(),
                               mWindowProps.mScreenLocationX, mWindowProps.mScreenLocationY,
                               mWindowProps.mWidth, mWindowProps.mHeight,
                               mWindowProps.mFlags);

    if (!mWindow)
    {
        XN_CORE_ERROR(SDL_GetError());

        return false;
    }

    mContext = SDL_GL_CreateContext(mWindow);
    SDL_GL_MakeCurrent(mWindow, mContext);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        XN_CORE_ERROR("Failed to load Glad.");

        return false;
    }

    mIsInitialized = true;

    return true;
}

void Xeno::Window::Display() const
{
    SDL_GL_SwapWindow(mWindow);
}

void Xeno::Window::ProcessEvents(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_WINDOWEVENT:
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWindowProps.mWidth = event.window.data1;
            mWindowProps.mHeight = event.window.data2;
            glViewport(0, 0, mWindowProps.mWidth, mWindowProps.mHeight);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Xeno::Window::SetWindowProps(WindowProperties props)
{
    mWindowProps = std::move(props);
}

void Xeno::Window::Resize(const uint32_t width, const uint32_t height)
{
    SDL_SetWindowSize(mWindow, width, height);
}

void Xeno::Window::SetWidth(const uint32_t value)
{
    SDL_SetWindowSize(mWindow, value, mWindowProps.mHeight);
}

uint32_t Xeno::Window::GetWidth()
{
    return mWindowProps.mWidth;
}

void Xeno::Window::SetHeight(const uint32_t value)
{
    SDL_SetWindowSize(mWindow, mWindowProps.mWidth, value);
}

uint32_t Xeno::Window::GetHeight()
{
    return mWindowProps.mHeight;
}

glm::vec2 Xeno::Window::GetCenter()
{
    return glm::vec2(mWindowProps.mWidth / 2, mWindowProps.mHeight / 2);
}

float Xeno::Window::GetAspectRatio()
{
    return (float)mWindowProps.mWidth / mWindowProps.mHeight;
}

bool Xeno::Window::IsMinimized() const
{
    return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MINIMIZED;
}
