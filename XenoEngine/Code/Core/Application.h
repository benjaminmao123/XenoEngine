#pragma once

#include "Core/Core.h"
#include "Core/Window.h"

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
        Window mWindow;
        SDL_Event mEvent;
        bool mIsRunning = false;

        uint32_t mVAO, mVBO, mShader;
        std::vector<float> mVertices;

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";
    };
}