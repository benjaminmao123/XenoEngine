#include "pch.h"
#include "Component/SpriteRendererComponent.h"
#include "Component/SpriteComponent.h"
#include "Renderer/Graphics/Shader.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity.h"
#include "Resource/ResourceManager.h"
#include "Component/MeshFilterComponent.h"

Xeno::SpriteRendererComponent::SpriteRendererComponent(Entity* owner) :
    RendererComponent(owner)
{
    GetEntity()->AddComponent<SpriteComponent>();
    GetEntity()->AddComponent<MeshFilterComponent>();
}

void Xeno::SpriteRendererComponent::LoadShader(const std::string& name, 
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

void Xeno::SpriteRendererComponent::OnStart()
{
    mSprite = GetEntity()->GetComponent<SpriteComponent>();
    mMeshFilter = GetEntity()->GetComponent<MeshFilterComponent>();
    mShader = ResourceManager::GetShader("default");
}

void Xeno::SpriteRendererComponent::OnRender() const
{
    Renderer::Submit({ &GetTransform(), mSprite->GetColor(), 
                     mSprite->GetTexture(), mMeshFilter->GetMesh(), mShader });
}