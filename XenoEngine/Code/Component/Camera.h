#pragma once

#include "Core/Core.h"
#include "Component/Transform.h"
#include "Component/Component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
                                 const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                                 ProjectionType type = ProjectionType::PERSPECTIVE);

        void SetProjectionType(ProjectionType type);
        [[nodiscard]] ProjectionType GetProjectionType() const;
        [[nodiscard]] glm::mat4 GetViewProjection() const;
        [[nodiscard]] glm::mat4 GetProjection() const;
        [[nodiscard]] glm::mat4 GetView() const;

        void SetFOV(float fov);
        [[nodiscard]] float GetFOV() const;
        void SetNear(float nearPlane);
        [[nodiscard]] float GetNear() const;
        void SetFar(float farPlane);
        [[nodiscard]] float GetFar() const;

    private:
        ProjectionType mProjectionType;
        float mFOV = 45.0f;
        float mNear = 0.01f;
        float mFar = 1000.0f;
    };
}