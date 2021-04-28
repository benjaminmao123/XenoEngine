#pragma once

#include "Core/Core.h"
#include "Entity/EntityManager.h"
#include "Component/Camera.h"

#include <string>

namespace Xeno
{
    class Entity;

    class XENO_API Scene
    {
    public:
        virtual ~Scene() = default;

        Entity* CreateEntity(std::string name);
        void DestroyEntity(const std::string& name);

        void SetName(std::string name);
        [[nodiscard]] const std::string& GetName() const;

        Entity* GetEntity(const std::string& name);
        [[nodiscard]] const Entity* GetEntity(const std::string& name) const;

        void SetMainCamera(Camera* camera);
        const Camera* GetMainCamera() const;

    protected:
        virtual void OnCreate();
        virtual void OnAwake();
        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnExit();

    private:
        explicit Scene(std::string name);

        void AddEntity(const std::shared_ptr<Entity>& entity);

        void Create();
        void Awake();
        void Start();
        void Update();
        void Render() const;
        void Exit();
        void ProcessRemovals();

        std::string mName;
        EntityManager mEntityManager;
        Camera* mMainCamera = nullptr;

        friend class SceneManager;
        friend class Application;
    };
}