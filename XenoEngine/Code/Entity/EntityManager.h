#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

#include <vector>
#include <memory>
#include <string>
#include <queue>

namespace Xeno
{
    class Entity;

    class XENO_API EntityManager : public NonCopyable
    {
    public:
        void Awake();
        void Start();
        void Update();
        void Render() const;
        void ProcessRemovals();

        void AddEntity(const std::shared_ptr<Entity>& entity);
        Entity* CreateEntity(std::string name);
        void DestroyEntity(const std::string& name);
        Entity* GetEntity(const std::string& name);
        [[nodiscard]] const Entity* GetEntity(const std::string& name) const;

    private:
        std::vector<std::shared_ptr<Entity>> mEntities;
        std::queue<std::shared_ptr<Entity>> mDestroyedEntities;
    };
}