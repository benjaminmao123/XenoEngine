#pragma once

#include "Core/Core.h"

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_pixels.h>
#include <string>
#include <glm/vec2.hpp>
#include <cstdint>

namespace Xeno
{
    class XENO_API Window
    {
    public:
        struct WindowProperties
        {
            std::string mTitle = "My App";
            int32_t mScreenLocationX = SDL_WINDOWPOS_CENTERED;
            int32_t mScreenLocationY = SDL_WINDOWPOS_CENTERED;
            uint32_t mFlags = SDL_WINDOW_OPENGL;
            uint32_t mWidth = 800;
            uint32_t mHeight = 600;
        };

        ~Window();

        void Update();

        bool ConstructWindow();

        void Clear(unsigned char r, 
                   unsigned char g, 
                   unsigned char b, 
                   unsigned char a) const;
        void Clear(const SDL_Color& color) const;

        [[nodiscard]] static uint32_t GetWidth();
        [[nodiscard]] static uint32_t GetHeight();
        [[nodiscard]] static glm::vec2 GetCenter();
        [[nodiscard]] static float GetAspectRatio();

    private:
        explicit Window(const WindowProperties& props);

        static inline WindowProperties mWindowProps;

        SDL_Window* mWindow;
        SDL_GLContext mContext;

        friend class Application;
    };
}