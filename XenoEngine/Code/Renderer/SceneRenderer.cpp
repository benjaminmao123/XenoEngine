#include "pch.h"
#include "SceneRenderer.h"
#include "Core/Assert.h"
#include "Core/Window.h"
#include "Resource/ResourceManager.h"
#include "Renderer/Graphics/VertexArray.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/Shader.h"
#include "Renderer/Graphics/ElementBuffer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

void Xeno::SceneRenderer::Submit(const RenderCommand& command)
{
    sCommandBuffer.emplace_back(command);
}

void Xeno::SceneRenderer::Clear(const uint8_t r,
                                const uint8_t g,
                                const uint8_t b,
                                const uint8_t a,
                                const uint32_t flags) const
{
    glClearColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
    glClear(flags);
}

void Xeno::SceneRenderer::Clear(const Color& color, const uint32_t flags) const
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(flags);
}

void Xeno::SceneRenderer::Init()
{
    if (mData.mVAO || mData.mVBO || mData.mEBO)
    {
        XN_CORE_WARN("SceneRenderer is already initialized.");

        return;
    }

    const auto whiteTexture = std::make_shared<Texture>("default_white", 1, 1, 
                                                        GL_RGB, GL_RGB, 
                                                        GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, 
                                                        GL_LINEAR, GL_LINEAR, 
                                                        false);
    uint32_t whiteTextureData = 0xffffffff;
    whiteTexture->SetData(&whiteTextureData);
    ResourceManager::AddTexture(whiteTexture);

    auto shader = std::make_shared<Shader>("default");
    shader->AddShader({ "Assets/Shaders/vertex.glsl", Shader::ShaderType::VERTEX });
    shader->AddShader({ "Assets/Shaders/frag.glsl", Shader::ShaderType::FRAGMENT });
    ResourceManager::AddShader(shader);
    shader->Bind();

    mData.mVAO = std::make_shared<VertexArray>();
    mData.mVBO = std::make_shared<VertexBuffer>(GL_DYNAMIC_DRAW);
    mData.mEBO = std::make_shared<ElementBuffer>();

    mData.mVBO->PushElement({ "Position", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Color", 4, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "UV", 2, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Normal", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Tangent", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "BiTangent", 3, GL_FLOAT, sizeof(float) });

    mData.mVAO->AddBuffer(mData.mVBO, mData.mEBO);
}

void Xeno::SceneRenderer::Render()
{
    Clear(Color::Gray(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mData.mVAO->Bind();

    if (SceneManager::GetActiveScene()->GetMainCamera()->GetProjectionType() == Camera::ProjectionType::PERSPECTIVE)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    for (const auto& command : sCommandBuffer)
    {
        const glm::mat4 mvp = SceneManager::GetActiveScene()->GetMainCamera()->GetViewProjection() *
            command.mTransform->GetModelMatrix();

        if (!command.mShader)
        {
            XN_CORE_ASSERT(false, "Trying to render without a shader!");

            return;
        }

        command.mShader->Bind();
        command.mShader->SetMat4("uMVP", mvp);
        command.mShader->SetFloat4("uColor", command.mColor.ToVec4());

        if (!command.mTexture)
            ResourceManager::GetTexture("default_white")->Bind();
        else
            command.mTexture->Bind();

        mData.mVBO->SetDataNew(&command.mMesh->mVertices[0], 
                               (uint32_t)command.mMesh->mVertices.size() * sizeof(Mesh::Vertex), 
                               GL_DYNAMIC_DRAW);

        if (!command.mMesh->mIndices.empty())
        {
            mData.mEBO->SetIndicesNew(&command.mMesh->mIndices[0],
                                      (uint32_t)command.mMesh->mIndices.size(),
                                      GL_DYNAMIC_DRAW);
            mData.mEBO->Bind();

            glDrawElements((GLenum)command.mMesh->mTopology, mData.mEBO->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
        else
            glDrawArrays((GLenum)command.mMesh->mTopology, 0, (uint32_t)command.mMesh->mVertices.size());
    }

    sCommandBuffer.clear();
}