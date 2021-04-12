#include "pch.h"
#include "EntityManager.h"
#include "Entity/Entity.h"

void Xeno::EntityManager::Awake()
{
	for (const auto& entity : mEntities)
	{
		if (!entity->mIsDestroyed)
			entity->Awake();
	}
}

void Xeno::EntityManager::Start()
{
	for (const auto& entity : mEntities)
	{
		if (!entity->mIsDestroyed && entity->IsActiveInHierarchy())
			entity->Start();
	}
}

void Xeno::EntityManager::Update()
{
	for (const auto& entity : mEntities)
	{
		if (!entity->mIsDestroyed && entity->IsActiveInHierarchy())
			entity->Update();
	}
}

void Xeno::EntityManager::Render() const
{
	for (const auto& entity : mEntities)
	{
		if (!entity->mIsDestroyed && entity->IsActiveInHierarchy())
			entity->Render();
	}
}

void Xeno::EntityManager::ProcessRemovals()
{
	while (!mDestroyedEntities.empty())
		mDestroyedEntities.pop();
}

void Xeno::EntityManager::AddEntity(const std::shared_ptr<Entity>& entity)
{
	mEntities.emplace_back(entity);
}

Xeno::Entity* Xeno::EntityManager::CreateEntity(std::string name)
{
	auto entity = std::make_shared<Entity>(std::move(name));
	mEntities.emplace_back(entity);

	return entity.get();
}

void Xeno::EntityManager::DestroyEntity(const std::string& name)
{
	const auto entityIt = std::find_if(mEntities.begin(),mEntities.end(),
[&](const std::shared_ptr<Entity>& entity)
    {
        return entity->GetName() == name;
    });

	if (entityIt == mEntities.end())
		return;

	(*entityIt)->mIsDestroyed = true;
	mEntities.erase(entityIt);
	mDestroyedEntities.emplace(std::move(*entityIt));
}

Xeno::Entity* Xeno::EntityManager::GetEntity(const std::string& name)
{
	const auto entityIt = std::find_if(mEntities.begin(), mEntities.end(),
[&](const std::shared_ptr<Entity>& entity)
	{
		return entity->GetName() == name;
	});

	if (entityIt == mEntities.end())
		return nullptr;

	return entityIt->get();
}

const Xeno::Entity* Xeno::EntityManager::GetEntity(const std::string& name) const
{
	const auto entityIt = std::find_if(mEntities.begin(), mEntities.end(),
[&](const std::shared_ptr<Entity>& entity)
	{
		return entity->GetName() == name;
	});

	if (entityIt == mEntities.end())
		return nullptr;

	return entityIt->get();
}
