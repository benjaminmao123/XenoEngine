#include "pch.h"
#include "Component/Component.h"
#include "Entity/Entity.h"
#include "Component/Transform.h"

Xeno::Component::Component(Entity* owner) :
	mOwner(std::move(owner))
{ }

Xeno::Component::~Component() = default;

void Xeno::Component::SetEnabled(const bool state)
{
	mIsEnabled = state;

	if (!mIsStartCalled)
	{
		mIsStartCalled = true;
		OnStart();
	}

	OnEnable();
}

bool Xeno::Component::IsEnabled() const
{
	return mIsEnabled;
}

Xeno::Entity* Xeno::Component::GetEntity()
{
	return mOwner;
}

const Xeno::Entity* Xeno::Component::GetEntity() const
{
	return mOwner;
}

Xeno::Transform& Xeno::Component::GetTransform()
{
	return mOwner->GetTransform();
}

const Xeno::Transform& Xeno::Component::GetTransform() const
{
	return mOwner->GetTransform();
}

void Xeno::Component::OnAwake()
{ }

void Xeno::Component::OnStart()
{ }

void Xeno::Component::OnUpdate()
{ }

void Xeno::Component::OnEnable()
{ }

void Xeno::Component::OnDisable()
{ }

void Xeno::Component::OnDestroy()
{ }