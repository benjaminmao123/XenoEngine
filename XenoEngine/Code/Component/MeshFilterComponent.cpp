#include "pch.h"
#include "Component/MeshFilterComponent.h"
#include "Renderer/Mesh/Mesh.h"

Xeno::MeshFilterComponent::MeshFilterComponent(Entity* owner) :
    Component(owner)
{ }

void Xeno::MeshFilterComponent::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    mMesh = mesh;
}

const Xeno::Mesh* Xeno::MeshFilterComponent::GetMesh() const
{
    return mMesh.get();
}
