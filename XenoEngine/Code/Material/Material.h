#pragma once

#include "Core/Core.h"
#include "Graphics/Color.h"
#include "Resource/ResourceManager.h"

#include <memory>
#include <unordered_map>

namespace Xeno
{
    class Texture;
    class Shader;

    class XENO_API Material
    {
    public:
        enum class TextureMap
        {
            NONE,
            DIFFUSE,
            SPECULAR,
            NORMAL,
            HEIGHT
        };

        Material() = default;

        template <typename T>
        void SetValue(const T& value)
        {
            
        }

        void SetTexture(Texture* texture);
        [[nodiscard]] const Texture* GetTexture() const;
        void SetDiffuseMap(Texture* map);
        [[nodiscard]] const Texture* GetDiffuseMap() const;
        void SetSpecularMap(Texture* map);
        [[nodiscard]] const Texture* GetSpecularMap() const;
        void SetNormalMap(Texture* map);
        [[nodiscard]] const Texture* GetNormalMap() const;
        void SetHeightMap(Texture* map);
        [[nodiscard]] const Texture* GetHeightMap() const;
        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;
        void SetShader(Shader* shader);
        [[nodiscard]] Shader* GetShader() const;
        void SetShininess(float value);
        [[nodiscard]] float GetShininess() const;

    private:
        Shader* mShader = nullptr;

        Texture* mDiffuseMap = nullptr;
        Texture* mSpecularMap = nullptr;
        Texture* mNormalMap = nullptr;
        Texture* mHeightMap = nullptr;
        Texture* mTexture = nullptr;

        std::unordered_map<std::string, float> mFloatUniforms;
        
        Color mColor;
        float mShininess = 32.0f;
    };
}