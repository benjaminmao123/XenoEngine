#pragma once

#include "Core/Core.h"
#include "Renderer/Graphics/Color.h"

#include <memory>
#include <glm/glm.hpp>

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
        void SetDiffuseMap(const std::shared_ptr<Texture>& map);
        [[nodiscard]] const Texture* GetDiffuseMap() const;
        void SetSpecularMap(const std::shared_ptr<Texture>& map);
        [[nodiscard]] const Texture* GetSpecularMap() const;
        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;
        void SetShader(const std::shared_ptr<Shader>& shader);
        [[nodiscard]] Shader* GetShader() const;
        void SetShininess(float value);
        [[nodiscard]] float GetShininess() const;

    private:
        std::shared_ptr<Shader> mShader = nullptr;

        std::shared_ptr<Texture> mDiffuseMap = nullptr;
        std::shared_ptr<Texture> mSpecularMap = nullptr;
        std::shared_ptr<Texture> mTexture = nullptr;
        
        Color mColor;
        float mShininess = 32.0f;
    };
}