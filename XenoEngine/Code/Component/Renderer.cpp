#include "pch.h"
#include "Component/Renderer.h"

Xeno::Renderer::Renderer(Entity* owner) :
	Component(owner)
{ }

Xeno::Renderer::~Renderer() = default;

void Xeno::Renderer::OnRender() const
{ }