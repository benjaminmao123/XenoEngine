#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Renderer/Graphics/Color.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Mesh/Quad.h"

#include <string>

namespace Xeno
{
    class XENO_API Sprite final : public Component
    {
    public:
        explicit Sprite(Entity* owner = nullptr);

        void LoadTexture(std::string path);

        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;
        [[nodiscard]] const Texture* GetTexture() const;
        [[nodiscard]] const Quad& GetQuad() const;

    private:
        std::string mPath;
        Texture* mTexture = nullptr;
        Quad mQuad;
        Color mColor;
    };
}