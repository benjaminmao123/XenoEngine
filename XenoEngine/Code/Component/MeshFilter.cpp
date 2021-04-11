#include "pch.h"
#include "Component/MeshFilter.h"
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

void Xeno::MeshFilter::SetTexture(Texture* texture)
{
    mTexture = texture;
}

const Xeno::Texture* Xeno::MeshFilter::GetTexture() const
{
    return mTexture;
}

void Xeno::MeshFilter::SetColor(const Color& color)
{
    mColor = color;
}

const Xeno::Color& Xeno::MeshFilter::GetColor() const
{
    return mColor;
}
