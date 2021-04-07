#pragma once

#include "Core/Core.h"
#include "Component/TransformComponent.h"
#include "Component/Component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Xeno
{
    class XENO_API CameraComponent final : public Component
    {
    public:
        enum class ProjectionType
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        explicit CameraComponent(Entity* owner,
                                 const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                                 ProjectionType type = ProjectionType::PERSPECTIVE);

        void SetProjectionType(ProjectionType type);
        [[nodiscard]] glm::mat4 GetViewProjection() const;
        [[nodiscard]] glm::mat4 GetProjection() const;
        [[nodiscard]] glm::mat4 GetView() const;

        void SetFov(float fov);
        [[nodiscard]] float GetFov() const;
        void SetNear(float nearPlane);
        [[nodiscard]] float GetNear() const;
        void SetFar(float farPlane);
        [[nodiscard]] float GetFar() const;

    private:
        ProjectionType mProjectionType;
        float mFov = 45.0f;
        float mNear = 0.0f;
        float mFar = 1000.0f;
    };
}