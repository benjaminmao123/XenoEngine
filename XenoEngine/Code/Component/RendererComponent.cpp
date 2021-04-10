#include "pch.h"
#include "Component/RendererComponent.h"

Xeno::RendererComponent::RendererComponent(Entity* owner) :
	Component(owner)
{ }

Xeno::RendererComponent::~RendererComponent() = default;

void Xeno::RendererComponent::OnRender() const
{ }