#pragma once

#include <string>

namespace Xeno
{
    class Application
    {
    public:
        Application(std::string name);
        
        void Run();

    private:
        std::string mAppName;
    };

    Application* CreateApplication();
}