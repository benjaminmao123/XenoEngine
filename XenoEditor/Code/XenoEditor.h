#pragma once

#include <Xeno.h>

class XenoEditor : public Application
{
public:
    explicit XenoEditor(Window::WindowProperties props);

protected:
    void OnRun() override;
    void OnUpdate() override;
    
private:

};