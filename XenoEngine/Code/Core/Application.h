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

int main(int argc, char* argv[]);

namespace Xeno
{
    class XENO_API Application : public NonCopyable
    {
    public:
        virtual ~Application();
        
        static void Quit();
 
        static Window& GetGameWindow();

    protected:
        Application(Window::WindowProperties props);

        virtual void OnRun();
        virtual void OnUpdate();
        virtual void OnExit();
        //virtual void OnRender() const;

    private:
        void Run();

        void PollEvents();
        void Awake();
        void Start();
        void Update();
        void Render() const;
        void Exit();

        Logger mLogger;
        static inline Window sWindow;
        Input mInput;
        Time mTime;
        SceneRenderer mRenderer;
        ResourceManager mResourceManager;
        SceneManager mSceneManager;
        SDL_Event mEvent;
        static inline bool sIsRunning = false;

        friend int ::main(int argc, char* argv[]);
    };
}