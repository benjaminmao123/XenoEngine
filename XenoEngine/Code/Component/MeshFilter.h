#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Renderer/Graphics/Color.h"

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
        void SetTexture(Texture* texture);
        [[nodiscard]] const Texture* GetTexture() const;
        void SetColor(const Color& color);
        const Color& GetColor() const;

    private:
        std::shared_ptr<Mesh> mMesh = nullptr;
        Texture* mTexture = nullptr;
        Color mColor;
    };
}