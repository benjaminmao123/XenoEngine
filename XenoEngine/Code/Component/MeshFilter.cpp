#include "pch.h"
#include "MeshFilter.h"
#include "Renderer/Mesh/Mesh.h"

Xeno::MeshFilter::MeshFilter(Entity* owner) :
    Component(owner)
{ }

void Xeno::MeshFilter::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
    mMesh = mesh;
}

const Xeno::Mesh* Xeno::MeshFilter::GetMesh() const
{
    return mMesh.get();
}
