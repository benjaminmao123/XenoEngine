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
#include "Component/Light.h"
#include "Entity/Entity.h"
#include "Renderer/Material/Material.h"

void Xeno::SceneRenderer::Submit(const RenderCommand& command)
{
    sCommandBuffer.emplace_back(command);
}

void Xeno::SceneRenderer::RegisterLight(const Light* light)
{
    sLights.emplace_back(light);
}

void Xeno::SceneRenderer::UnregisterLight(const Light* light)
{
    sLights.erase(std::remove_if(sLights.begin(), sLights.end(),
    [&](const Light* l)
    {
        return l->GetEntity()->GetInstanceID() == light->GetEntity()->GetInstanceID();
    }), sLights.end());
}

void Xeno::SceneRenderer::SetClearColor(const Color& color)
{
    sClearColor = color;
}

const Xeno::Color& Xeno::SceneRenderer::GetClearColor()
{
    return sClearColor;
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
        "Default White",
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
    Clear(sClearColor, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mData.mVAO->Bind();

    //process commands
    for (const auto& command : sCommandBuffer)
    {
        if (!command.mMaterial->GetShader())
            XN_CORE_ASSERT(false, "Trying to render without a shader!");

        command.mMaterial->GetShader()->Bind();
        command.mMaterial->GetShader()->SetMat4("uModel", command.mTransform->GetModelMatrix());

        const glm::mat4 vp = SceneManager::GetActiveScene()->GetMainCamera()->GetViewProjection();

        command.mMaterial->GetShader()->SetMat4("uViewProjection", vp);
        command.mMaterial->GetShader()->SetFloat4("uColor", command.mMaterial->GetColor().ToVec4());

        switch (command.mType)
        {
        case RenderCommand::CommandType::MESH:
            RenderMesh(command);
            break;
        case RenderCommand::CommandType::SPRITE:
            RenderSprite(command);
            break;
        case RenderCommand::CommandType::GUI:
            RenderGUI(command);
            break;
        }

        mData.mVBO->SetDataNew(&command.mMesh->mVertices[0], 
                               (uint32_t)command.mMesh->mVertices.size() * sizeof(Mesh::Vertex), 
                               GL_DYNAMIC_DRAW);

        if (!command.mMesh->mIndices.empty())
        {
            mData.mEBO->SetIndicesNew(&command.mMesh->mIndices[0],
                                      (uint32_t)command.mMesh->mIndices.size(),
                                      GL_DYNAMIC_DRAW);

            Draw(command.mMesh->mTopology, *mData.mVAO, *mData.mEBO, *command.mMaterial->GetShader());
        }
        else
            Draw(command.mMesh->mTopology, *mData.mVAO, *mData.mVBO, *command.mMaterial->GetShader());
    }

    mData.mFBO->Unbind();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    Clear(Color::White(), GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, mData.mFBO->GetColorAttachment(0));

    mData.mVBO->SetDataNew(&mData.mScreenQuad.mVertices[0], 
                           (uint32_t)mData.mScreenQuad.mVertices.size() * sizeof(Mesh::Vertex),
                           GL_DYNAMIC_DRAW);
    mData.mEBO->SetIndicesNew(&mData.mScreenQuad.mIndices[0],
                              (uint32_t)mData.mScreenQuad.mIndices.size(),
                              GL_DYNAMIC_DRAW);

    Draw(mData.mScreenQuad.mTopology, *mData.mVAO, *mData.mEBO, *ResourceManager::GetShader("Screen Shader"));

    sCommandBuffer.clear();
}

void Xeno::SceneRenderer::RenderMesh(const RenderCommand& command) const
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    const glm::vec3& viewPosition = SceneManager::GetActiveScene()->GetMainCamera()->GetTransform().GetPosition();

    command.mMaterial->GetShader()->SetFloat3("uViewPosition", viewPosition);
    command.mMaterial->GetShader()->SetFloat("uMaterial.mShininess", command.mMaterial->GetShininess());
    command.mMaterial->GetShader()->SetInt("uNumLights", sLights.size());

    for (size_t i = 0; i < sLights.size(); ++i)
    {
        command.mMaterial->GetShader()->SetInt("uLights[" + std::to_string(i) + "].mLightType", 
                                               (int32_t)sLights[i]->GetLightType());

        switch (sLights[i]->GetLightType())
        {
        case Light::LightType::DIRECTIONAL:
        case Light::LightType::POINT:
        case Light::LightType::SPOT:
            command.mMaterial->GetShader()->SetFloat3("uLights[" + std::to_string(i) + "].mPosition",
                                                      sLights[i]->GetTransform().GetPosition());
            command.mMaterial->GetShader()->SetFloat3("uLights[" + std::to_string(i) + "].mAmbient",
                                                      sLights[i]->GetAmbient());
            command.mMaterial->GetShader()->SetFloat3("uLights[" + std::to_string(i) + "].mDiffuse",
                                                      sLights[i]->GetDiffuse());
            command.mMaterial->GetShader()->SetFloat3("uLights[" + std::to_string(i) + "].mSpecular",
                                                      sLights[i]->GetSpecular());
            command.mMaterial->GetShader()->SetFloat4("uLights[" + std::to_string(i) + "].mColor",
                                                      sLights[i]->GetColor().ToVec4());
            command.mMaterial->GetShader()->SetFloat("uLights[" + std::to_string(i) + "].mIntensity",
                                                     sLights[i]->GetIntensity());
            switch (sLights[i]->GetLightType())
            {
            case Light::LightType::DIRECTIONAL:
                command.mMaterial->GetShader()->SetFloat3("uLights[" + std::to_string(i) + "].mDirection",
                                                          sLights[i]->GetTransform().GetForward());
                break;
            case Light::LightType::POINT:
            case Light::LightType::SPOT:
                command.mMaterial->GetShader()->SetFloat("uLights[" + std::to_string(i) + "].mConstant",
                                                         sLights[i]->GetConstant());
                command.mMaterial->GetShader()->SetFloat("uLights[" + std::to_string(i) + "].mLinear",
                                                         sLights[i]->GetLinear());
                command.mMaterial->GetShader()->SetFloat("uLights[" + std::to_string(i) + "].mQuadratic",
                                                         sLights[i]->GetQuadratic());
                switch (sLights[i]->GetLightType())
                {
                case Light::LightType::SPOT:
                    command.mMaterial->GetShader()->SetFloat3("uLights[" + std::to_string(i) + "].mDirection",
                                                              sLights[i]->GetTransform().GetForward());
                    command.mMaterial->GetShader()->SetFloat("uLights[" + std::to_string(i) + "].mCutoff",
                                                             sLights[i]->GetCutoff());
                    command.mMaterial->GetShader()->SetFloat("uLights[" + std::to_string(i) + "].mOuterCutoff",
                                                             sLights[i]->GetOuterCutoff());
                    break;
                default:
                    break;
                }
                break;
            }
            break;
        }
    }

    command.mMaterial->GetTexture()->Bind();
}

void Xeno::SceneRenderer::RenderSprite(const RenderCommand& command) const
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    if (!command.mMaterial->GetTexture())
        ResourceManager::GetTexture("Default White")->Bind();
    else
        command.mMaterial->GetTexture()->Bind();
}

void Xeno::SceneRenderer::RenderGUI(const RenderCommand& command) const
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    if (!command.mMaterial->GetTexture())
        ResourceManager::GetTexture("Default White")->Bind();
    else
        command.mMaterial->GetTexture()->Bind();
}

void Xeno::SceneRenderer::Draw(const uint32_t topology, 
                               const VertexArray& vao, 
                               const VertexBuffer& vbo, 
                               const Shader& shader) const
{
    vao.Bind();
    shader.Bind();

    glDrawArrays(topology, 0, vbo.GetSize());
}

void Xeno::SceneRenderer::Draw(const uint32_t topology,
                               const VertexArray& vao, 
                               const ElementBuffer& ebo, 
                               const Shader& shader) const
{
    vao.Bind();
    ebo.Bind();
    shader.Bind();

    glDrawElements(topology, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
}
