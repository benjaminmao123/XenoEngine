#pragma once

#include "Core/Core.h"
#include "Renderer/Graphics/Color.h"

#include <memory>

namespace Xeno
{
    class Texture;
    class Shader;

    class XENO_API Material
    {
    public:
        Material();

        void SetTexture(const std::shared_ptr<Texture>& texture);
        [[nodiscard]] const Texture* GetTexture() const;
        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;
        void SetShader(const std::shared_ptr<Shader>& shader);
        [[nodiscard]] const Shader* GetShader() const;

    private:
        std::shared_ptr<Texture> mTexture = nullptr;
        std::shared_ptr<Shader> mShader = nullptr;
        Color mColor;
    };
}