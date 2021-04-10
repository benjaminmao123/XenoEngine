#pragma once

#include "Core/Core.h"
#include "Component/Component.h"

#include <memory>

namespace Xeno
{
    struct Mesh;

    class XENO_API MeshFilterComponent final : public Component
    {
    public:
        explicit MeshFilterComponent(Entity* owner = nullptr);

        void SetMesh(const std::shared_ptr<Mesh>& mesh);
        [[nodiscard]] const Mesh* GetMesh() const;

    private:
        std::shared_ptr<Mesh> mMesh = nullptr;
    };
}