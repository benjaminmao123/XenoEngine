#pragma once

#include "Core/Core.h"
#include "Component/Renderer.h"

namespace Xeno
{
    class MeshFilter;

    class XENO_API MeshRenderer final : public Renderer
    {
    public:
        explicit MeshRenderer(Entity* owner = nullptr);

    private:
        void OnStart() override;
        void OnRender() const override;

        const MeshFilter* mMeshFilter = nullptr;
    };
}