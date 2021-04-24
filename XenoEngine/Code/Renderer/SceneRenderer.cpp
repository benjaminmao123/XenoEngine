#include "pch.h"
#include "SceneRenderer.h"
#include "Core/Assert.h"
#include "Core/Application.h"
#include "Resource/ResourceManager.h"
#include "Renderer/Graphics/VertexArray.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/Shader.h"
#include "Renderer/Graphics/ElementBuffer.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Renderer/Graphics/FrameBuffer.h"

void Xeno::SceneRenderer::Submit(const RenderCommand& command)
{
    sCommandBuffer.emplace_back(command);
}

void Xeno::SceneRenderer::Clear(const uint8_t r, const uint8_t g, const uint8_t b, 
                                const uint8_t a, const uint32_t flags) const
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

    static uint8_t whiteTextureData[] = { 255, 255, 255, 255 };

    Texture::TextureProperties whiteTextureProps =
    {
        "white",
        1, 1,
        GL_RGBA, GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_REPEAT, GL_REPEAT,
        GL_LINEAR, GL_LINEAR
    };
    
    const auto whiteTexture = std::make_shared<Texture>(whiteTextureData, whiteTextureProps);
    ResourceManager::AddTexture(whiteTexture);

    auto meshShader = std::make_shared<Shader>("Default Shader");
    meshShader->AddShader({ "Assets/Shaders/DefaultVertex.glsl", GL_VERTEX_SHADER });
    meshShader->AddShader({ "Assets/Shaders/DefaultFragment.glsl", GL_FRAGMENT_SHADER });
    ResourceManager::AddShader(meshShader);

    auto screenShader = std::make_shared<Shader>("Screen Shader");
    screenShader->AddShader({ "Assets/Shaders/ScreenVertex.glsl", GL_VERTEX_SHADER });
    screenShader->AddShader({ "Assets/Shaders/ScreenFragment.glsl", GL_FRAGMENT_SHADER });
    ResourceManager::AddShader(screenShader);

    FrameBuffer::FrameBufferProperties props = 
    {
        Application::GetGameWindow().GetWidth(), Application::GetGameWindow().GetHeight(),
        { GL_RGB },
        GL_DEPTH24_STENCIL8
    };

    mData.mFBO = std::make_shared<FrameBuffer>(props);

    mData.mVAO = std::make_shared<VertexArray>();
    mData.mVBO = std::make_shared<VertexBuffer>(GL_DYNAMIC_DRAW);
    mData.mEBO = std::make_shared<ElementBuffer>();

    mData.mVBO->PushElement({ "Position", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Color", 4, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "UV", 2, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Normal", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Tangent", 3, GL_FLOAT, sizeof(float) });
    mData.mVBO->PushElement({ "Bitangent", 3, GL_FLOAT, sizeof(float) });

    mData.mVAO->AddBuffer(mData.mVBO, mData.mEBO);
}

void Xeno::SceneRenderer::ProcessEvents(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_WINDOWEVENT:
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mData.mFBO->Resize(event.window.data1, event.window.data2);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Xeno::SceneRenderer::Render() const
{
    mData.mFBO->Bind();

    glEnable(GL_DEPTH_TEST);
    Clear(Color::Gray(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mData.mVAO->Bind();

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
            ResourceManager::GetTexture("white")->Bind();
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

            glDrawElements(command.mMesh->mTopology, mData.mEBO->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
        else
            glDrawArrays(command.mMesh->mTopology, 0, (uint32_t)command.mMesh->mVertices.size());
    }

    mData.mFBO->Unbind();

    glDisable(GL_DEPTH_TEST);
    Clear(Color::White(), GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, mData.mFBO->GetColorAttachment(0));

    mData.mVBO->SetDataNew(&mData.mScreenQuad.mVertices[0], 
                           (uint32_t)mData.mScreenQuad.mVertices.size() * sizeof(Mesh::Vertex),
                           GL_DYNAMIC_DRAW);
    mData.mEBO->SetIndicesNew(&mData.mScreenQuad.mIndices[0],
                              (uint32_t)mData.mScreenQuad.mIndices.size(),
                              GL_DYNAMIC_DRAW);

    ResourceManager::GetShader("screenShader")->Bind();

    mData.mEBO->Bind();

    glDrawElements(mData.mScreenQuad.mTopology, mData.mEBO->GetCount(), GL_UNSIGNED_INT, nullptr);

    sCommandBuffer.clear();
}