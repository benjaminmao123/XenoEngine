#include "pch.h"
#include "MeshRenderer.h"

#include "Sprite.h"
#include "Component/MeshFilter.h"
#include "Entity/Entity.h"
#include "Renderer/SceneRenderer.h"

Xeno::MeshRenderer::MeshRenderer(Entity* owner) :
    Renderer(owner)
{
    GetEntity()->AddComponent<MeshFilter>();
}

void Xeno::MeshRenderer::OnStart()
{
    mMeshFilter = GetEntity()->GetComponent<MeshFilter>();
}

void Xeno::MeshRenderer::OnRender() const
{
    SceneRenderer::Submit(
    { 
        SceneRenderer::RenderCommand::CommandType::MESH, 
        &GetTransform(), 
        mMeshFilter->GetMesh(), 
        &GetMaterial() 
    });
}
