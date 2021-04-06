#include "pch.h"
#include "Renderer/Renderer.h"
#include "Core/Window.h"
#include "Resource/ResourceManager.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/ElementBuffer.h"

#include <memory>

Xeno::Renderer::RendererData Xeno::Renderer::mData;

void Xeno::Renderer::DrawQuad(const TransformComponent& transform, 
                              const CameraComponent& camera, 
                              const Color& color)
{
    mData.mVAO->Bind();

    const glm::mat4 mvp = camera.GetViewProjection() * transform.GetModelMatrix();
    const auto shader = ResourceManager::GetShader("sprite");

    if (shader)
    {
        shader->Bind();
        shader->SetMat4("uMVP", mvp);
        shader->SetFloat4("uColor", color.ToVec4());
    }

    glDrawElements(GL_TRIANGLES, mData.mEBO->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Xeno::Renderer::Init()
{
    mData.mQuad =
    {
         // positions       // uvs
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f    // top left 
    };

    mData.mIndices =
    {
        0, 1, 3,
        1, 2, 3
    };

    const auto shader = std::make_shared<Shader>("sprite");
    shader->AddShader({ "Assets/Shaders/vertex.glsl", Shader::ShaderType::VERTEX });
    shader->AddShader({ "Assets/Shaders/frag.glsl", Shader::ShaderType::FRAGMENT });
    ResourceManager::AddShader(shader);

    const auto texture = std::make_shared<Texture>("Assets/Textures/container.jpg");
    ResourceManager::AddTexture(texture);

    mData.mVAO = std::make_shared<VertexArray>();
    mData.mVBO = std::make_shared<VertexBuffer>();
    mData.mEBO = std::make_shared<ElementBuffer>();

    mData.mVBO->SetDataNew(&mData.mQuad[0], mData.mQuad.size() * sizeof(float), GL_STATIC_DRAW);
    mData.mVBO->PushElement({ "aPosition", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "aTexCoords", 2, GL_FLOAT, sizeof(float) });

    mData.mEBO->SetIndicesNew(&mData.mIndices[0], mData.mIndices.size(), GL_STATIC_DRAW);

    mData.mVAO->AddBuffer(mData.mVBO, mData.mEBO);
}
