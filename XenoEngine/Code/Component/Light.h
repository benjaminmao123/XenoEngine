#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Renderer/Graphics/Color.h"

#include <memory>

namespace Xeno
{
    class XENO_API Light final : public Component
    {
    public:
        enum class LightType
        {
            DIRECTIONAL,
            POINT,
            SPOT
        };

        explicit Light(Entity* owner = nullptr);

        void SetLightType(LightType type);
        [[nodiscard]] LightType GetLightType() const;
        void SetIntensity(float value);
        [[nodiscard]] float GetIntensity() const;
        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;

    private:
        LightType mType;
        float mIntensity = 1.0f;
        Color mColor;
    };
}