#include "pch.h"
#include "Scene.h"
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

void Xeno::Scene::SetMainCamera(Camera* camera)
{
	mMainCamera = camera;
}

const Xeno::Camera* Xeno::Scene::GetMainCamera() const
{
	return mMainCamera;
}

void Xeno::Scene::OnCreate()
{ }

void Xeno::Scene::OnAwake()
{ }

void Xeno::Scene::OnStart()
{ }

void Xeno::Scene::OnUpdate()
{ }

void Xeno::Scene::OnExit()
{ }

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

void Xeno::Scene::Create()
{
	OnCreate();
}

void Xeno::Scene::Awake()
{
	OnAwake();

	mEntityManager.Awake();
}

void Xeno::Scene::Start()
{
	OnStart();

	mEntityManager.Start();
}

void Xeno::Scene::Update()
{
	OnUpdate();

	mEntityManager.Update();
}

void Xeno::Scene::Render() const
{
	mEntityManager.Render();
}

void Xeno::Scene::Exit()
{
	OnExit();
}

void Xeno::Scene::ProcessRemovals()
{
	mEntityManager.ProcessRemovals();
}
