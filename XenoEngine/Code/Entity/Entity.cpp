#include "pch.h"
#include "Entity.h"
#include "Component/Transform.h"
#include "Component/Renderer.h"

Xeno::Entity::Entity(std::string name, const glm::vec3& pos) :
	mName(std::move(name))
{
	mInstanceID = sInstanceID++;
	mTransform = AddComponent<Transform>();
	mTransform->SetPosition(pos);
}

void Xeno::Entity::Awake()
{
	for (const auto& component : mComponents)
	{
		if (!component->mIsAwakeCalled)
		{
			component->OnAwake();
			component->mIsAwakeCalled = true;
		}
	}

	for (const auto& entity : mChildren)
		entity->Awake();
}

void Xeno::Entity::Start()
{
	for (const auto& component : mComponents)
	{
		if (!component->mIsStartCalled && component->IsEnabled())
		{
			component->OnStart();
			component->mIsStartCalled = true;
		}
	}

	for (const auto& entity : mChildren)
		entity->Start();
}

void Xeno::Entity::Update()
{
	for (const auto& component : mComponents)
	{
		if (component->IsEnabled())
			component->OnUpdate();
	}

	for (const auto& entity : mChildren)
		entity->Update();
}

void Xeno::Entity::Render() const
{
	for (const auto& component : mComponents)
	{
		if (component->IsEnabled())
		{
			const auto renderComponent = std::dynamic_pointer_cast<Renderer>(component);

			if (std::dynamic_pointer_cast<Renderer>(component))
				renderComponent->OnRender();
		}
	}

	for (const auto& entity : mChildren)
		entity->Render();
}

void Xeno::Entity::SetName(std::string name)
{
	mName = std::move(name);

	if (mName.empty())
		mName = "New Entity";
}

const std::string& Xeno::Entity::GetName() const
{
	return mName;
}

void Xeno::Entity::SetActive(const bool state)
{
	mIsActive = state;
	Start();
}

bool Xeno::Entity::IsActiveSelf() const
{
	return mIsActive;
}

bool Xeno::Entity::IsActiveInHierarchy() const
{
	if (!mParent)
		return mIsActive;

	return mParent->IsActiveInHierarchy() && mIsActive;
}

void Xeno::Entity::SetParent(Entity* entity)
{
	mParent = entity;
}

Xeno::Entity* Xeno::Entity::GetParent()
{
	return mParent;
}

const Xeno::Entity* Xeno::Entity::GetParent() const
{
	return mParent;
}

uint32_t Xeno::Entity::GetInstanceID() const
{
	return mInstanceID;
}

Xeno::Transform& Xeno::Entity::GetTransform()
{
	return *mTransform;
}

const Xeno::Transform& Xeno::Entity::GetTransform() const
{
	return *mTransform;
}