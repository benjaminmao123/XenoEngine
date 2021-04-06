#pragma once

#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "Utility/NonCopyable.h"
#include "Resource/ResourceManager.h"

#include <SDL2/SDL_events.h>

namespace Xeno
{
    class XENO_API Application : public NonCopyable
    {
    public:
        Application(const Window::WindowProperties& props);
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

        Logger mLogger;
        Window mWindow;
        Input mInput;
        Time mTime;
        Renderer mRenderer;
        ResourceManager mResourceManager;
        SDL_Event mEvent;
        bool mIsRunning = false;
    };
}