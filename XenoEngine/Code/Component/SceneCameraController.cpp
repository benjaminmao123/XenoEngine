#include "pch.h"
#include "Component/SceneCameraController.h"
#include "Component/Camera.h"
#include "Entity/Entity.h"
#include "Core/Input.h"
#include "Core/Time.h"

Xeno::SceneCameraController::SceneCameraController(Entity* owner) :
    Component(owner)
{ }

void Xeno::SceneCameraController::SetPanSpeed(const float value)
{
    mCameraPanSpeed = value;
}

float Xeno::SceneCameraController::GetPanSpeed() const
{
    return mCameraPanSpeed;
}

void Xeno::SceneCameraController::SetSensitivity(const float value)
{
    mSensitivity = value;
}

float Xeno::SceneCameraController::GetSensitivity() const
{
    return mSensitivity;
}

void Xeno::SceneCameraController::OnStart()
{
    mCamera = GetEntity()->GetComponent<Camera>();
}

void Xeno::SceneCameraController::OnUpdate()
{
    if (mCamera)
    {
        if (mCamera->GetProjectionType() == Camera::ProjectionType::ORTHOGRAPHIC)
        {
            if (Input::GetKey(Input::KeyCode::W))
                mCamera->GetTransform().Translate(0, -mCameraPanSpeed * Time::GetDeltaTime(), 0);
            if (Input::GetKey(Input::KeyCode::S))
                mCamera->GetTransform().Translate(0, mCameraPanSpeed * Time::GetDeltaTime(), 0);
            if (Input::GetKey(Input::KeyCode::A))
                mCamera->GetTransform().Translate(-mCameraPanSpeed * Time::GetDeltaTime(), 0, 0);
            if (Input::GetKey(Input::KeyCode::D))
                mCamera->GetTransform().Translate(mCameraPanSpeed * Time::GetDeltaTime(), 0, 0);
        }
        else
        {
            if (Input::GetKey(Input::KeyCode::W))
                mCamera->GetTransform().Translate(mCamera->GetTransform().GetForward() * mCameraPanSpeed * Time::GetDeltaTime());
            if (Input::GetKey(Input::KeyCode::S))
                mCamera->GetTransform().Translate(-mCamera->GetTransform().GetForward() * mCameraPanSpeed * Time::GetDeltaTime());
            if (Input::GetKey(Input::KeyCode::A))
                mCamera->GetTransform().Translate(-mCamera->GetTransform().GetRight() * mCameraPanSpeed * Time::GetDeltaTime());
            if (Input::GetKey(Input::KeyCode::D))
                mCamera->GetTransform().Translate(mCamera->GetTransform().GetRight() * mCameraPanSpeed * Time::GetDeltaTime());

            const glm::vec2 mouse = Input::GetAxis(Input::AxisType::MOUSE);

            mCamera->GetTransform().Rotate(0.0f, mouse.x * mSensitivity, 0.0f, Transform::Space::SELF);
            mCamera->GetTransform().Rotate(mouse.y * mSensitivity, 0.0f, 0.0f, Transform::Space::WORLD);
        }
    }
}
