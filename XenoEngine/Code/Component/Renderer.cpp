#include "pch.h"
#include "Renderer.h"

Xeno::Renderer::Renderer(Entity* owner) :
	Component(owner)
{ }

Xeno::Renderer::~Renderer() = default;

void Xeno::Renderer::SetMaterial(const Material& material)
{
	mMaterial = material;
}

const Xeno::Material& Xeno::Renderer::GetMaterial() const
{
	return mMaterial;
}

Xeno::Material& Xeno::Renderer::GetMaterial()
{
	return mMaterial;
}

void Xeno::Renderer::OnRender() const
{ }
