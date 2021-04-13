#pragma once

#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Core/Logger.h"
#include "Renderer/SceneRenderer.h"
#include "Utility/NonCopyable.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"

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

    protected:
        virtual void OnRun();
        virtual void OnUpdate();

    private:
        void Awake();
        void Start();
        void Update();
        void Render() const;
        void OnExit();

        Logger mLogger;
        Window mWindow;
        Input mInput;
        Time mTime;
        SceneRenderer mRenderer;
        ResourceManager mResourceManager;
        SceneManager mSceneManager;
        SDL_Event mEvent;
        bool mIsRunning = false;
    };
}