#pragma once

#include <Xeno.h>
#include <memory>

using namespace std;

namespace XenoEditor
{
    class XenoEditor final : public Xeno::Application
    {
    public:
        explicit XenoEditor(Xeno::Window::WindowProperties props);

    protected:
        void OnRun() override;
        void OnUpdate() override;

    private:
        shared_ptr<VertexArray> mVAO;
        shared_ptr<VertexBuffer> mVBO;

        Scene* mScene = nullptr;
        
        float mTriangle[9] = 
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        }; 
    };
}