#include "pch.h"
#include "Window.h"

#include <glad.h>

Xeno::Window::~Window()
{
    SDL_DestroyWindow(mWindow);
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

    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow(mWindowProps.mTitle.c_str(), 
                               mWindowProps.mScreenLocationX, mWindowProps.mScreenLocationY, 
                               mWindowProps.mWidth, mWindowProps.mHeight, 
                               mWindowProps.mFlags);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    mContext = SDL_GL_CreateContext(mWindow);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
}
