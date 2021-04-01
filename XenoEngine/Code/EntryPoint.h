#pragma once

#include "Core/Application.h"

extern Xeno::Application* Xeno::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Xeno::CreateApplication();
    app->Run();

    return 0;
}