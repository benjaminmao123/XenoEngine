#include "pch.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Core/Logger.h"

#include <algorithm>

void Xeno::SceneManager::AddScene(const std::string& name)
{
    const auto sceneIt = std::find_if(sScenes.begin(), sScenes.end(),
    [&](const std::shared_ptr<const Scene>& scene)
    {
        return scene->GetName() == name;
    });

    if (sceneIt != sScenes.end())
    {
        XN_CORE_ERROR("Scene has already been added: {0}.", name);

        return;
    }

    sScenes.emplace_back(std::shared_ptr<Scene>(new Scene(name)));
}

void Xeno::SceneManager::LoadScene(const std::string& name)
{
	if (sScenes.empty())
	{
		XN_CORE_ERROR("Trying to load a scene when scene "
					  "list is empty!");

		return;
	}

	if (sActiveScene)
		sActiveScene->OnExit();

	sActiveScene = GetScene(name);

	if (sActiveScene)
		sActiveScene->OnCreate();
}

void Xeno::SceneManager::LoadScene(const std::size_t index)
{
	if (sScenes.empty())
	{
		XN_CORE_WARN("Trying to load a scene when scene "
					 "list is empty!");

		return;
	}

	if (sActiveScene)
		sActiveScene->OnExit();

	sActiveScene = GetScene(index);

	if (sActiveScene)
		sActiveScene->OnCreate();
}

Xeno::Scene* Xeno::SceneManager::GetScene(const std::string& name)
{
	if (sScenes.empty())
		return nullptr;

	const auto sceneIt =
		std::find_if(sScenes.begin(), sScenes.end(),
[&](const std::shared_ptr<Scene>& scene)
    {
	    return scene->GetName() == name;
    });

	if (sceneIt == sScenes.end())
		return nullptr;

	return sceneIt->get();
}

Xeno::Scene* Xeno::SceneManager::GetScene(const std::size_t index)
{
	if (sScenes.empty() || index >= sScenes.size())
	{
		XN_CORE_WARN("Specified scene index is larger than "
					 "the scene list!");

		return nullptr;
	}

	return sScenes[index].get();
}

Xeno::Scene* Xeno::SceneManager::GetActiveScene()
{
	return sActiveScene;
}

void Xeno::SceneManager::Awake()
{
	if (sActiveScene)
		sActiveScene->Awake();
}

void Xeno::SceneManager::Start()
{
	if (sActiveScene)
		sActiveScene->Start();
}

void Xeno::SceneManager::Update()
{
	if (sActiveScene)
		sActiveScene->Update();
}

void Xeno::SceneManager::Render() const
{
	if (sActiveScene)
		sActiveScene->Render();
}

void Xeno::SceneManager::OnExit()
{
	if (sActiveScene)
		sActiveScene->OnExit();
}

void Xeno::SceneManager::ProcessRemovals()
{
	if (sActiveScene)
		sActiveScene->ProcessRemovals();
}

