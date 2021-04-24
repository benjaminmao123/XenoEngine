#include "XenoEditor.h"

#include <glad/glad.h>

using namespace Xeno;

XenoEditor::XenoEditor::XenoEditor(Xeno::Window::WindowProperties props) :
    Application(std::move(props))
{ }

void XenoEditor::XenoEditor::OnRun()
{
    SceneManager::AddScene("sandbox");
    mScene = SceneManager::GetScene("sandbox");

    mVAO = make_shared<VertexArray>();

    mVBO = make_shared<VertexBuffer>(mTriangle, sizeof(mTriangle));
    mVBO->PushElement({ "Position", 2, GL_FLOAT, false });

    mVAO->AddBuffer(mVBO);
}

void XenoEditor::XenoEditor::OnUpdate()
{
    mVAO->Bind();
}
