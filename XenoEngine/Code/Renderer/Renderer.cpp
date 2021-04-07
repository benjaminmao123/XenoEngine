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

void Xeno::Renderer::Submit(const std::shared_ptr<RenderCommand>& command)
{
    sCommandBuffer.emplace_back(command);
}

void Xeno::Renderer::DrawQuad(const TransformComponent& transform, 
                              const CameraComponent& camera, 
                              const Color& color)
{
    sData.mVAO->Bind();

    const glm::mat4 mvp = camera.GetViewProjection() * transform.GetModelMatrix();
    auto* const shader = ResourceManager::GetShader("sprite");

    if (shader)
    {
        shader->Bind();
        shader->SetMat4("uMVP", mvp);
        shader->SetFloat4("uColor", color.ToVec4());
    }

    glDrawElements(GL_TRIANGLES, sData.mEBO->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Xeno::Renderer::Init() const
{
    sData.mQuad =
    {
         // positions       // uvs
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f    // top left 
    };

    sData.mIndices =
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

    sData.mVAO = std::make_shared<VertexArray>();
    sData.mVBO = std::make_shared<VertexBuffer>();
    sData.mEBO = std::make_shared<ElementBuffer>();

    sData.mVBO->SetDataNew(&sData.mQuad[0], sData.mQuad.size() * sizeof(float), GL_STATIC_DRAW);
    sData.mVBO->PushElement({ "aPosition", 3, GL_FLOAT, sizeof(float) });
    sData.mVBO->PushElement({ "aTexCoords", 2, GL_FLOAT, sizeof(float) });

    sData.mEBO->SetIndicesNew(&sData.mIndices[0], sData.mIndices.size(), GL_STATIC_DRAW);

    sData.mVAO->AddBuffer(sData.mVBO, sData.mEBO);
}
