#pragma once

#include "Core/Core.h"

#include <string>
#include <vector>

namespace Xeno
{
    class Scene;

    class XENO_API SceneManager
    {
    public:
        static void AddScene(const std::string& name);
        static void LoadScene(const std::string& name);
        static void LoadScene(std::size_t index);

        static Scene* GetScene(const std::string& name);
        static Scene* GetScene(std::size_t index);
        static Scene* GetActiveScene();

    private:
        SceneManager() = default;

        void Awake();
        void Start();
        void Update();
        void Render() const;
        void Exit();
        void ProcessRemovals();

        static inline std::vector<std::shared_ptr<Scene>> sScenes;
        static inline Scene* sActiveScene = nullptr;

        friend class Application;
    };
}