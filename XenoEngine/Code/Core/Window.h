#pragma once

#include "Core.h"

#include <SDL2/SDL.h>
#include <string>
#include <GLM/vec2.hpp>

namespace Xeno
{
    struct WindowProperties
    {
        std::string mTitle = "My App";
        int32_t mScreenLocationX = SDL_WINDOWPOS_CENTERED;
        int32_t mScreenLocationY = SDL_WINDOWPOS_CENTERED;
        uint32_t mFlags = SDL_WINDOW_OPENGL;
        uint32_t mWidth = 800;
        uint32_t mHeight = 600;
    };

    class XENO_API Window
    {
    public:
        ~Window();

        static uint32_t GetWidth();
        static uint32_t GetHeight();
        static glm::vec2 GetCenter();
        static float GetAspectRatio();

    private:
        Window(const WindowProperties& props);

        static inline WindowProperties mWindowProps;
        SDL_Window* mWindow;
        SDL_GLContext mContext;

        friend class Application;
    };
}