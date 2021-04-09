#include "pch.h"
#include "Core/Window.h"
#include "Core/Logger.h"

#include <SDL2/SDL.h>

Xeno::Window::~Window()
{
    SDL_DestroyWindow(mWindow);
}

bool Xeno::Window::ConstructWindow()
{
    mWindow = SDL_CreateWindow(sWindowProps.mTitle.c_str(),
                               sWindowProps.mScreenLocationX, sWindowProps.mScreenLocationY,
                               sWindowProps.mWidth, sWindowProps.mHeight,
                               sWindowProps.mFlags);

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

    return true;
}

void Xeno::Window::Display() const
{
    SDL_GL_SwapWindow(mWindow);
}

uint32_t Xeno::Window::GetWidth()
{
    return sWindowProps.mWidth;
}

uint32_t Xeno::Window::GetHeight()
{
    return sWindowProps.mHeight;
}

glm::vec2 Xeno::Window::GetCenter()
{
    return glm::vec2(sWindowProps.mWidth / 2, sWindowProps.mHeight / 2);
}

float Xeno::Window::GetAspectRatio()
{
    return static_cast<float>(sWindowProps.mWidth) / sWindowProps.mHeight;
}

Xeno::Window::Window(const WindowProperties& props)
{
    sWindowProps.mTitle = props.mTitle;
    sWindowProps.mScreenLocationX = props.mScreenLocationX;
    sWindowProps.mScreenLocationY = props.mScreenLocationY;
    sWindowProps.mWidth = props.mWidth;
    sWindowProps.mHeight = props.mHeight;
    sWindowProps.mFlags = props.mFlags;
}
