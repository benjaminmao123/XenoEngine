#include "pch.h"
#include "SceneCameraController.h"
#include "Component/Camera.h"
#include "Entity/Entity.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Core/Application.h"

#include <algorithm>
#include <iostream>

using namespace std;

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

void Xeno::SceneCameraController::SetZoomFactor(const float value)
{
    mZoomFactor = value;
}

float Xeno::SceneCameraController::GetZoomFactor() const
{
    return mZoomFactor;
}

void Xeno::SceneCameraController::OnStart()
{
    mCamera = GetEntity()->GetComponent<Camera>();
}

void Xeno::SceneCameraController::OnUpdate()
{
    if (mCamera)
    {
        UpdateMovement();
        UpdateRotation();
        UpdateZoom();
    }
}

void Xeno::SceneCameraController::UpdateMovement()
{
    if (mCamera->GetProjectionType() == Camera::ProjectionType::ORTHOGRAPHIC)
    {
        if (Input::GetKey(Input::KeyCode::W))
            mCamera->GetTransform().Translate(0, -mCameraPanSpeed *
                                              Time::GetDeltaTime(), 0);
        if (Input::GetKey(Input::KeyCode::A))
            mCamera->GetTransform().Translate(-mCameraPanSpeed *
                                              Time::GetDeltaTime(), 0, 0);
        if (Input::GetKey(Input::KeyCode::S))
            mCamera->GetTransform().Translate(0, mCameraPanSpeed *
                                              Time::GetDeltaTime(), 0);
        if (Input::GetKey(Input::KeyCode::D))
            mCamera->GetTransform().Translate(mCameraPanSpeed *
                                              Time::GetDeltaTime(), 0, 0);
    }
    else
    {
        if (Input::GetKey(Input::KeyCode::W))
            mCamera->GetTransform().Translate(mCamera->GetTransform().GetForward() *
                                              mCameraPanSpeed * Time::GetDeltaTime());
        if (Input::GetKey(Input::KeyCode::A))
            mCamera->GetTransform().Translate(-mCamera->GetTransform().GetRight() *
                                              mCameraPanSpeed * Time::GetDeltaTime());
        if (Input::GetKey(Input::KeyCode::S))
            mCamera->GetTransform().Translate(-mCamera->GetTransform().GetForward() *
                                              mCameraPanSpeed * Time::GetDeltaTime());
        if (Input::GetKey(Input::KeyCode::D))
            mCamera->GetTransform().Translate(mCamera->GetTransform().GetRight() *
                                              mCameraPanSpeed * Time::GetDeltaTime());
    }
}

void Xeno::SceneCameraController::UpdateRotation()
{
    if (mCamera->GetProjectionType() == Camera::ProjectionType::ORTHOGRAPHIC)
    {
        // TODO
    }
    else
    {
        const glm::vec2 mouse = Input::GetAxis(Input::AxisType::MOUSE);

        mCamera->GetTransform().Rotate(0.0f, mouse.x * mSensitivity *
                                       Time::GetDeltaTime(), 0.0f, Transform::Space::SELF);
        mCamera->GetTransform().Rotate(mouse.y * mSensitivity *
                                       Time::GetDeltaTime(), 0.0f, 0.0f, Transform::Space::WORLD);
    }
}

void Xeno::SceneCameraController::UpdateZoom()
{
    if (mCamera->GetProjectionType() == Camera::ProjectionType::ORTHOGRAPHIC)
    {
        if (Input::GetMouseScrollDelta().y)
        {
            const float zoom = -Input::GetMouseScrollDelta().y * mZoomFactor * 0.25f;
            const float deltaHeight = zoom * (mCamera->GetTop() - mCamera->GetBottom() +
                                              (mCamera->GetRight() - mCamera->GetLeft())) / 2;
            const float deltaWidth = deltaHeight * Application::GetGameWindow().GetAspectRatio();

            mCamera->SetLeft(mCamera->GetLeft() - deltaWidth);
            mCamera->SetRight(mCamera->GetRight() + deltaWidth);
            mCamera->SetBottom(mCamera->GetBottom() + deltaHeight);
            mCamera->SetTop(mCamera->GetTop() - deltaHeight);
        }
    }
    else
    {
        if (Input::GetMouseScrollDelta().y)
        {
            const float zoom = mZoomFactor * Input::GetMouseScrollDelta().y;
            mCamera->SetFOV(mCamera->GetFOV() - zoom);

            if (mCamera->GetFOV() < 1.0f)
                mCamera->SetFOV(1.0f);
            if (mCamera->GetFOV() > 100.0f)
                mCamera->SetFOV(100.0f);
        }
    }
}
