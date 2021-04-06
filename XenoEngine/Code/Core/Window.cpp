#include "pch.h"
#include "Core/Window.h"
#include "Core/Logger.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>

Xeno::Window::~Window()
{
    SDL_DestroyWindow(mWindow);
}

bool Xeno::Window::ConstructWindow()
{
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

    return true;
}

void Xeno::Window::Clear(const unsigned char r, 
                         const unsigned char g, 
                         const unsigned char b, 
                         const unsigned char a) const
{
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Xeno::Window::Clear(const SDL_Color& color) const
{
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Xeno::Window::Display() const
{
    SDL_GL_SwapWindow(mWindow);
}

uint32_t Xeno::Window::GetWidth()
{
    return mWindowProps.mWidth;
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
    return static_cast<float>(mWindowProps.mWidth) / mWindowProps.mHeight;
}

Xeno::Window::Window(const WindowProperties& props)
{
    mWindowProps.mTitle = props.mTitle;
    mWindowProps.mScreenLocationX = props.mScreenLocationX;
    mWindowProps.mScreenLocationY = props.mScreenLocationY;
    mWindowProps.mWidth = props.mWidth;
    mWindowProps.mHeight = props.mHeight;
    mWindowProps.mFlags = props.mFlags;
}
