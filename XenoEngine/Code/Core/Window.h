#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Renderer/Graphics/Color.h"

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_pixels.h>
#include <string>
#include <glm/glm.hpp>
#include <cstdint>
#include <glad/glad.h>

namespace Xeno
{
    class XENO_API Window : public NonCopyable
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

        bool ConstructWindow();

        void Clear(unsigned char r, 
                   unsigned char g, 
                   unsigned char b, 
                   unsigned char a,
                   GLenum flags) const;
        void Clear(const Color& color, GLenum flags) const;
        void Display() const;

        static uint32_t GetWidth();
        static uint32_t GetHeight();
        static glm::vec2 GetCenter();
        static float GetAspectRatio();

    private:
        explicit Window(const WindowProperties& props);

        static inline WindowProperties sWindowProps;

        SDL_Window* mWindow;
        SDL_GLContext mContext;

        friend class Application;
    };
}
