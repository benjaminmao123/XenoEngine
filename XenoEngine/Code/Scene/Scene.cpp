#include "pch.h"
#include "Scene/Scene.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"
#include "Utility/Utility.h"

Xeno::Scene::Scene(std::string name)
{
	const Scene* exists = SceneManager::GetScene(name);

	if (name.empty() || exists)
	{
		mName = "Scene " + Utility::GetDateTime();
		XN_CORE_WARN("Scene with the same name already exists: {0}. Scene renamed to: {1}", name, mName);

		return;
	}

	mName = std::move(name);
}

void Xeno::Scene::SetName(std::string name)
{
	const Scene* exists = SceneManager::GetScene(name);

	if (name.empty() || exists)
	{
		XN_CORE_WARN("Scene with the same name already exists: {0}.", name);

		return;
	}

	mName = std::move(name);
}

const std::string& Xeno::Scene::GetName() const
{
	return mName;
}

Xeno::Entity* Xeno::Scene::GetEntity(const std::string& name)
{
	return mEntityManager.GetEntity(name);
}

const Xeno::Entity* Xeno::Scene::GetEntity(const std::string& name) const
{
	return mEntityManager.GetEntity(name);
}

void Xeno::Scene::SetMainCamera(CameraComponent* camera)
{
	mMainCamera = camera;
}

const Xeno::CameraComponent* Xeno::Scene::GetMainCamera() const
{
	return mMainCamera;
}

void Xeno::Scene::AddEntity(const std::shared_ptr<Entity>& entity)
{
	return mEntityManager.AddEntity(entity);
}

Xeno::Entity* Xeno::Scene::CreateEntity(std::string name)
{
	return mEntityManager.CreateEntity(std::move(name));
}

void Xeno::Scene::DestroyEntity(const std::string& name)
{
	mEntityManager.DestroyEntity(name);
}

void Xeno::Scene::OnCreate()
{ }

void Xeno::Scene::Awake()
{
	mEntityManager.Awake();
}

void Xeno::Scene::Start()
{
	mEntityManager.Start();
}

void Xeno::Scene::Update()
{
	mEntityManager.Update();
}

void Xeno::Scene::Render() const
{
	mEntityManager.Render();
}

void Xeno::Scene::OnExit()
{ }

void Xeno::Scene::ProcessRemovals()
{
	mEntityManager.ProcessRemovals();
}
