#include "pch.h"
#include "Renderer/Renderer.h"
#include "Core/Window.h"
#include "Resource/ResourceManager.h"
#include "Renderer/Graphics/VertexArray.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/Shader.h"
#include "Renderer/Graphics/ElementBuffer.h"

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
        shader->SetFloat4("vColor", color.ToVec4());
    }

    glDrawElements(GL_TRIANGLES, sData.mEBO->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Xeno::Renderer::Clear(const unsigned char r, 
                           const unsigned char g, 
                           const unsigned char b, 
                           const unsigned char a, 
                           const GLenum flags)
{
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    glClear(flags);
}

void Xeno::Renderer::Clear(const Color& color, const GLenum flags)
{
    glClearColor(color.ToFloat().r, color.ToFloat().g, color.ToFloat().b, color.ToFloat().a);
    glClear(flags);
}

void Xeno::Renderer::Init() const
{
    auto containerTexture = std::make_shared<Texture>("Assets/Textures/container.jpg");
    ResourceManager::AddTexture(containerTexture);

    auto whiteTexture = std::make_shared<Texture>(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    ResourceManager::AddTexture(whiteTexture);

    auto shader = std::make_shared<Shader>("sprite");
    shader->AddShader({ "Assets/Shaders/vertex.glsl", Shader::ShaderType::VERTEX });
    shader->AddShader({ "Assets/Shaders/frag.glsl", Shader::ShaderType::FRAGMENT });
    ResourceManager::AddShader(shader);
    shader->Bind();

    int32_t samplers[sData.sMaxTextureUnits];

    for (uint32_t i = 0; i < 32; ++i)
        samplers[i] = i;

    shader->SetIntArr("uTextures", samplers, sData.sMaxTextureUnits);
    sData.mTextureUnits[0] = whiteTexture;

    sData.mVAO = std::make_shared<VertexArray>();
    sData.mVBO = std::make_shared<VertexBuffer>(sData.sMaxVertices * sizeof(Quad::Vertex), GL_DYNAMIC_DRAW);
    sData.mEBO = std::make_shared<ElementBuffer>();
    sData.mVBO->PushElement({ "aPosition", 3, GL_FLOAT, sizeof(float) });
    sData.mVBO->PushElement({ "aTexCoords", 2, GL_FLOAT, sizeof(float) });

    //sData.mEBO->SetIndicesNew(&sData.mIndices[0], sData.mIndices.size(), GL_STATIC_DRAW);

    sData.mVAO->AddBuffer(sData.mVBO, sData.mEBO);
}
