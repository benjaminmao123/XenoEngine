#include "pch.h"
#include "SceneCameraController.h"
#include "Component/Camera.h"
#include "Entity/Entity.h"
#include "Core/Input.h"
#include "Core/Time.h"

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

void Xeno::SceneCameraController::SetZoomLevel(float value)
{
    mZoomFactor = value;
}

float Xeno::SceneCameraController::GetZoomLevel() const
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

            if (Input::GetMouseScrollDelta().y)
            {
                mZoomFactor = -Input::GetMouseScrollDelta().y * 0.25f;
                const float deltaHeight = mZoomFactor * (mCamera->GetTop() - mCamera->GetBottom() + (mCamera->GetRight() - mCamera->GetLeft())) / 2;
                const float deltaWidth = deltaHeight * Window::GetAspectRatio();

                mCamera->SetLeft(mCamera->GetLeft() - deltaWidth);
                mCamera->SetRight(mCamera->GetRight() + deltaWidth);
                mCamera->SetBottom(mCamera->GetBottom() + deltaHeight);
                mCamera->SetTop(mCamera->GetTop() - deltaHeight);
            }
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

            mCamera->GetTransform().Rotate(0.0f, mouse.x * mSensitivity * Time::GetDeltaTime(), 0.0f, Transform::Space::SELF);
            mCamera->GetTransform().Rotate(mouse.y * mSensitivity * Time::GetDeltaTime(), 0.0f, 0.0f, Transform::Space::WORLD);

            if (Input::GetMouseScrollDelta().y)
            {
                mZoomFactor = Input::GetMouseScrollDelta().y * 2;
                mCamera->SetFOV(mCamera->GetFOV() - mZoomFactor);

                if (mCamera->GetFOV() < 1.0f)
                    mCamera->SetFOV(1.0f);
                if (mCamera->GetFOV() > 100.0f)
                    mCamera->SetFOV(100.0f);
            }
        }
    }
}
