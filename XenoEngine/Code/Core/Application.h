#pragma once

#include "Core.h"
#include "Window.h"

#include <string>
#include <SDL2/SDL.h>

namespace Xeno
{
    class XENO_API Application
    {
    public:
        Application(std::string name = "My App");
        ~Application();
        
        void Run();
        void PollEvents();
        void OnExit();

    private:
        std::string mAppName;
        Window mWindow;
        SDL_Event mEvent;
        bool mIsRunning = false;
    };
}