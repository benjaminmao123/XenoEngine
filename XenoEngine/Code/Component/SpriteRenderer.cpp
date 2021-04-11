#include "pch.h"
#include "Component/SpriteRenderer.h"
#include "Component/Sprite.h"
#include "Renderer/Graphics/Shader.h"
#include "Renderer/SceneRenderer.h"
#include "Entity/Entity.h"
#include "Resource/ResourceManager.h"

Xeno::SpriteRenderer::SpriteRenderer(Entity* owner) :
    Renderer(owner)
{
    GetEntity()->AddComponent<Sprite>();
    mShader = ResourceManager::GetShader("default");
}

void Xeno::SpriteRenderer::LoadShader(const std::string& name,
                                      const std::vector<Shader::ShaderSource>& sources)
{
    if (mShader)
    {
        if (mShader->GetName() == name)
            return;
    }

    if (!ResourceManager::AddShader(std::make_shared<Shader>(name, sources)))
        return;

    mShader = ResourceManager::GetShader(name);
}

void Xeno::SpriteRenderer::OnStart()
{
    mSprite = GetEntity()->GetComponent<Sprite>();
}

void Xeno::SpriteRenderer::OnRender() const
{
    SceneRenderer::Submit({ &GetTransform(), mSprite->GetColor(),
        mSprite->GetTexture(), &mSprite->GetQuad(), mShader });
}