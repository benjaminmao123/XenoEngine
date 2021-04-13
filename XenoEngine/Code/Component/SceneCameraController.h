#pragma once

#include "Core/Core.h"
#include "Component/Component.h"

namespace Xeno
{
    class Camera;

    class XENO_API SceneCameraController final : public Component
    {
    public:
        explicit SceneCameraController(Entity* owner = nullptr);

        void SetPanSpeed(float value);
        [[nodiscard]] float GetPanSpeed() const;
        void SetSensitivity(float value);
        [[nodiscard]] float GetSensitivity() const;
        void SetZoomFactor(float value);
        [[nodiscard]] float GetZoomFactor() const;

    private:
        void OnStart() override;
        void OnUpdate() override;

        Camera* mCamera = nullptr;
        float mCameraPanSpeed = 10.0f;
        float mSensitivity = 10.0f;
        float mZoomFactor = 1.0f;
    };
}