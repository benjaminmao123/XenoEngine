#include "pch.h"
#include "Camera.h"
#include "Core/Application.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Xeno::Camera::Camera(Entity* owner,
                     const glm::vec3& position,
                     const ProjectionType type) :
    Component(owner),
    mLeft(0.0f), mRight(Application::GetGameWindow().GetWidth()),
    mBottom(Application::GetGameWindow().GetHeight()), mTop(0.0f)
{
    SetProjectionType(type);
    GetTransform().SetPosition(position);
}

void Xeno::Camera::SetProjectionType(const ProjectionType type)
{
    mProjectionType = type;

    if (mProjectionType == ProjectionType::ORTHOGRAPHIC)
    {
        if (mNear > 0.0f)
            mNear = 0.0f;
    }
    else
    {
        if (mNear <= 0.0f)
            mNear = 0.01f;
    }
}

Xeno::Camera::ProjectionType Xeno::Camera::GetProjectionType() const
{
    return mProjectionType;
}

float Xeno::Camera::GetFar() const
{
    return mFar;
}

void Xeno::Camera::SetLeft(const float value)
{
    mLeft = value;
}

float Xeno::Camera::GetLeft() const
{
    return mLeft;
}

void Xeno::Camera::SetRight(const float value)
{
    mRight = value;
}

float Xeno::Camera::GetRight() const
{
    return mRight;
}

void Xeno::Camera::SetBottom(const float value)
{
    mBottom = value;
}

float Xeno::Camera::GetBottom() const
{
    return mBottom;
}

void Xeno::Camera::SetTop(const float value)
{
    mTop = value;
}

float Xeno::Camera::GetTop() const
{
    return mTop;
}

glm::mat4 Xeno::Camera::GetViewProjection() const
{
    return GetProjection() * GetView();
}

glm::mat4 Xeno::Camera::GetProjection() const
{
    if (mProjectionType == ProjectionType::ORTHOGRAPHIC)
        return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);

    return glm::perspective(glm::radians(mFOV),
                            Application::GetGameWindow().GetAspectRatio(), 
                            mNear, mFar);
}

glm::mat4 Xeno::Camera::GetView() const
{
    return lookAt(GetTransform().GetPosition(),
                  GetTransform().GetPosition() + GetTransform().GetForward(),
                  GetTransform().GetUp());
}

void Xeno::Camera::SetFOV(const float value)
{
    mFOV = value;
}

float Xeno::Camera::GetFOV() const
{
    return mFOV;
}

void Xeno::Camera::SetNear(const float value)
{
    mNear = value;
}

float Xeno::Camera::GetNear() const
{
    return mNear;
}

void Xeno::Camera::SetFar(const float value)
{
    mFar = value;
}