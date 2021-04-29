#pragma once

#include "Core/Core.h"
#include "Component/Component.h"
#include "Graphics/Color.h"

#include <memory>
#include <glm/glm.hpp>

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

        explicit Light(Entity* owner = nullptr, LightType type = LightType::DIRECTIONAL);

        void SetLightType(LightType type);
        [[nodiscard]] LightType GetLightType() const;
        void SetIntensity(float value);
        [[nodiscard]] float GetIntensity() const;
        void SetColor(const Color& color);
        [[nodiscard]] const Color& GetColor() const;
        void SetAmbient(const glm::vec3& values);
        void SetAmbient(float v0, float v1, float v2);
        [[nodiscard]] const glm::vec3& GetAmbient() const;
        void SetDiffuse(const glm::vec3& values);
        void SetDiffuse(float v0, float v1, float v2);
        [[nodiscard]] const glm::vec3& GetDiffuse() const;
        void SetSpecular(const glm::vec3& values);
        void SetSpecular(float v0, float v1, float v2);
        [[nodiscard]] const glm::vec3& GetSpecular() const;
        void SetConstant(float value);
        [[nodiscard]] float GetConstant() const;
        void SetLinear(float value);
        [[nodiscard]] float GetLinear() const;
        void SetQuadratic(float value);
        [[nodiscard]] float GetQuadratic() const;
        void SetCutoff(float value);
        [[nodiscard]] float GetCutoff() const;
        void SetOuterCutoff(float value);
        [[nodiscard]] float GetOuterCutoff() const;

    private:
        void OnDestroy() override;

        LightType mType;
        glm::vec3 mAmbient = glm::vec3(0.05f, 0.05f, 0.05f);
        glm::vec3 mDiffuse = glm::vec3(0.4f, 0.4f, 0.4f);
        glm::vec3 mSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
        Color mColor;
        float mConstant = 1.0f;
        float mLinear = 0.09f;
        float mQuadratic = 0.032f;
        float mCutoff = glm::cos(glm::radians(12.5f));
        float mOuterCutoff = glm::cos(glm::radians(15.0f));
        float mIntensity = 1.0f;
    };
}