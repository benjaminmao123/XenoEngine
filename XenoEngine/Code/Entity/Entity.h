#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Core/Logger.h"

#include <memory>
#include <string>
#include <vector>

namespace Xeno
{
    class Component;
    class TransformComponent;

    class XENO_API Entity : public NonCopyable, std::enable_shared_from_this<Entity>
    {
    public:
        explicit Entity(std::string name = "");

        template <typename T, typename... Ts>
        T* AddComponent(Ts&&... args);
        template <typename T>
        T* GetComponent();
        template <typename T>
        const T* GetComponent() const;

        void SetName(std::string name);
        [[nodiscard]] const std::string& GetName() const;
        void SetActive(bool state);
        [[nodiscard]] bool IsActiveSelf() const;
        [[nodiscard]] bool IsActiveInHierarchy() const;
        void SetParent(Entity* entity);
        Entity* GetParent();
        [[nodiscard]] const Entity* GetParent() const;
        uint32_t GetInstanceID() const;

        TransformComponent& GetTransform();
        const TransformComponent& GetTransform() const;

    private:
        void Awake();
        void Start();
        void Update();
        void Render() const;

        std::string mName;
        static inline uint32_t sInstanceID = 0;
        uint32_t mInstanceID = 0;
        bool mIsActive = true;
        bool mIsDestroyed = false;

        std::vector<std::shared_ptr<Component>> mComponents;
        std::vector<std::shared_ptr<Entity>> mChildren;
        Entity* mParent = nullptr;
        TransformComponent* mTransform;

        friend class EntityManager;
    };

    template <typename T, typename ... Ts>
    T* Entity::AddComponent(Ts&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value,
                      "T must derive from component!");

        for (const auto& component : mComponents)
        {
            if (std::dynamic_pointer_cast<T>(component))
            {
                XN_CORE_WARN("Cannot add component. Component already exists!");

                return nullptr;
            }
        }

        auto component = std::make_shared<T>(this, std::forward<Ts>(args)...);
        mComponents.emplace_back(component);

        return component.get();
    }

    template <typename T>
    T* Entity::GetComponent()
    {
        for (const auto& component : mComponents)
        {
            std::shared_ptr<T> retComp = std::dynamic_pointer_cast<T>(component);

            if (retComp)
                return retComp.get();
        }

        return nullptr;
    }

    template <typename T>
    const T* Entity::GetComponent() const
    {
        for (const auto& component : mComponents)
        {
            std::shared_ptr<T> retComp = std::dynamic_pointer_cast<T>(component);

            if (retComp)
                return retComp.get();
        }

        return nullptr;
    }
}