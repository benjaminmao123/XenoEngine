#pragma once

#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include <string>
#include <SDL2/SDL_events.h>
#include <vector>

namespace Xeno
{
    class XENO_API Application
    {
    public:
        Application(std::string name = "My App");
        virtual ~Application();
        
        void Run();

        void PollEvents();
        void OnExit();

    protected:
        virtual void OnCreate();
        virtual void OnUpdate();

    private:
        void Create();
        void Update();

        std::string mAppName;
        Logger mLogger;
        Window mWindow;
        Input mInput;
        Time mTime;
        SDL_Event mEvent;
        bool mIsRunning = false;
    };
}