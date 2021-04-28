#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

#include <string>
#include <glm/glm.hpp>
#include <cstdint>
#include <SDL2/SDL.h>

namespace Xeno
{
    class XENO_API Window : public NonCopyable
    {
    public:
        enum class FullScreenMode
        {
            NONE,
            FULLSCREEN,
            BORDERLESS_WINDOWED
        };

        struct WindowProperties
        {
            std::string mTitle = "My App";
            int32_t mScreenLocationX = SDL_WINDOWPOS_CENTERED;
            int32_t mScreenLocationY = SDL_WINDOWPOS_CENTERED;
            uint32_t mFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
            uint32_t mWidth = 800;
            uint32_t mHeight = 600;
        };

        ~Window();

        bool ConstructWindow();

        void Display() const;
        void ProcessEvents(const SDL_Event& event);
        void SetWindowProps(WindowProperties props);
        void Resize(uint32_t width, uint32_t height);
        void SetFullScreenMode(FullScreenMode mode);

        void SetWidth(uint32_t value);
        uint32_t GetWidth();
        void SetHeight(uint32_t value);
        uint32_t GetHeight();
        glm::vec2 GetCenter();
        float GetAspectRatio();

        bool IsMinimized() const;

    private:
        Window() = default;
        explicit Window(WindowProperties props);

        WindowProperties mWindowProps;

        SDL_Window* mWindow = nullptr;
        SDL_GLContext mContext;

        bool mIsInitialized = false;
        FullScreenMode mFullScreenMode = FullScreenMode::NONE;

        friend class Application;
    };
}
