#include "pch.h"
#include "Component/MeshRenderer.h"

#include "Sprite.h"
#include "Component/MeshFilter.h"
#include "Resource/ResourceManager.h"
#include "Entity/Entity.h"
#include "Renderer/SceneRenderer.h"

Xeno::MeshRenderer::MeshRenderer(Entity* owner) :
    Renderer(owner)
{
    GetEntity()->AddComponent<MeshFilter>();
    mShader = ResourceManager::GetShader("default");
}

void Xeno::MeshRenderer::LoadShader(const std::string& name, const std::vector<Shader::ShaderSource>& sources)
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

void Xeno::MeshRenderer::OnStart()
{
    mMeshFilter = GetEntity()->GetComponent<MeshFilter>();
}

void Xeno::MeshRenderer::OnRender() const
{
    SceneRenderer::Submit({ &GetTransform(), mMeshFilter->GetColor(),
        mMeshFilter->GetTexture(), mMeshFilter->GetMesh(), mShader });
}
