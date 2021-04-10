#pragma once

#include "Core/Core.h"
#include "Entity/EntityManager.h"
#include "Component/CameraComponent.h"

#include <string>

namespace Xeno
{
    class Entity;

    class XENO_API Scene
    {
    public:
        Entity* CreateEntity(std::string name);
        void DestroyEntity(const std::string& name);

        void SetName(std::string name);
        [[nodiscard]] const std::string& GetName() const;

        Entity* GetEntity(const std::string& name);
        [[nodiscard]] const Entity* GetEntity(const std::string& name) const;

        void SetMainCamera(CameraComponent* camera);
        const CameraComponent* GetMainCamera() const;

    private:
        explicit Scene(std::string name);

        void AddEntity(const std::shared_ptr<Entity>& entity);

        void OnCreate();
        void Awake();
        void Start();
        void Update();
        void Render() const;
        void OnExit();
        void ProcessRemovals();

        std::string mName;
        EntityManager mEntityManager;
        CameraComponent* mMainCamera = nullptr;

        friend class SceneManager;
        friend class Application;
    };
}