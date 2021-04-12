#pragma once

#include "Core/Core.h"
#include "Component/Component.h"

#include <memory>

namespace Xeno
{
    struct Mesh;
    class Texture;

    class XENO_API MeshFilter final : public Component
    {
    public:
        explicit MeshFilter(Entity* owner = nullptr);

        void SetMesh(const std::shared_ptr<Mesh>& mesh);
        [[nodiscard]] const Mesh* GetMesh() const;

    private:
        std::shared_ptr<Mesh> mMesh = nullptr;
    };
}