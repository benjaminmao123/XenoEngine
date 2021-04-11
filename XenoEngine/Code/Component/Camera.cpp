#include "pch.h"
#include "Camera.h"
#include "Core/Window.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Xeno::Camera::Camera(Entity* owner,
                     const glm::vec3& position,
                     const ProjectionType type) :
    Component(owner)
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

glm::mat4 Xeno::Camera::GetViewProjection() const
{
    return GetProjection() * GetView();
}

glm::mat4 Xeno::Camera::GetProjection() const
{
    if (mProjectionType == ProjectionType::ORTHOGRAPHIC)
        return glm::ortho(0.0f,
            (float)Window::GetWidth(),
            (float)Window::GetHeight(),
            0.0f,
            mNear,
            mFar);

    return glm::perspective(glm::radians(mFOV),
        Window::GetAspectRatio(),
        mNear, mFar);
}

glm::mat4 Xeno::Camera::GetView() const
{
    return lookAt(GetTransform().GetPosition(),
          GetTransform().GetPosition() + GetTransform().GetForward(),
          GetTransform().GetUp());
}

void Xeno::Camera::SetFOV(const float fov)
{
    mFOV = fov;
}

float Xeno::Camera::GetFOV() const
{
    return mFOV;
}

void Xeno::Camera::SetNear(const float nearPlane)
{
    mNear = nearPlane;
}

float Xeno::Camera::GetNear() const
{
    return mNear;
}

void Xeno::Camera::SetFar(const float farPlane)
{
    mFar = farPlane;
}