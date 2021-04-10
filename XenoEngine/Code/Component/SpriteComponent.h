#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Renderer/Graphics/Color.h"
#include "Renderer/Graphics/Texture.h"

#include <string>

namespace Xeno
{
    class XENO_API SpriteComponent final : public Component
    {
    public:
        explicit SpriteComponent(Entity* owner = nullptr);

        void LoadTexture(std::string path);

        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;
        [[nodiscard]] const Texture* GetTexture() const;

    private:
        std::string mPath;
        Texture* mTexture = nullptr;
        Color mColor;
    };
}