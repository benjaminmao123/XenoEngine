#pragma once

#include "Core/Core.h"
#include "Component/Transform.h"
#include "Component/Component.h"

#include <glm/glm.hpp>

#include "Core/Window.h"

namespace Xeno
{
    class XENO_API Camera final : public Component
    {
    public:
        enum class ProjectionType
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        explicit Camera(Entity* owner = nullptr,
                        ProjectionType type = ProjectionType::PERSPECTIVE);

        void SetProjectionType(ProjectionType type);
        [[nodiscard]] ProjectionType GetProjectionType() const;
        [[nodiscard]] glm::mat4 GetViewProjection() const;
        [[nodiscard]] glm::mat4 GetProjection() const;
        [[nodiscard]] glm::mat4 GetView() const;

        void SetFOV(float value);
        [[nodiscard]] float GetFOV() const;
        void SetNear(float value);
        [[nodiscard]] float GetNear() const;
        void SetFar(float value);
        [[nodiscard]] float GetFar() const;
        void SetLeft(float value);
        [[nodiscard]] float GetLeft() const;
        void SetRight(float value);
        [[nodiscard]] float GetRight() const;
        void SetBottom(float value);
        [[nodiscard]] float GetBottom() const;
        void SetTop(float value);
        [[nodiscard]] float GetTop() const;

    private:
        ProjectionType mProjectionType;
        float mFOV = 45.0f;
        float mNear = 0.01f;
        float mFar = 1000.0f;
        float mLeft;
        float mRight;
        float mBottom;
        float mTop;
    };
}
