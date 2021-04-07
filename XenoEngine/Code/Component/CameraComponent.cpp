#include "pch.h"
#include "Component/CameraComponent.h"
#include "Core/Window.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Xeno::CameraComponent::CameraComponent(Entity* owner,
                                       const glm::vec3& position,
                                       const ProjectionType type) :
    Component(owner),
    mProjectionType(type)
{
    GetTransform().SetPosition(position);
}

void Xeno::CameraComponent::SetProjectionType(const ProjectionType type)
{
    mProjectionType = type;
}

float Xeno::CameraComponent::GetFar() const
{
    return mFar;
}

glm::mat4 Xeno::CameraComponent::GetViewProjection() const
{
    return GetProjection() * GetView();
}

glm::mat4 Xeno::CameraComponent::GetProjection() const
{
    if (mProjectionType == ProjectionType::ORTHOGRAPHIC)
    	return glm::ortho(0.0f,
    					  (float)Window::GetWidth(),
    					  (float)Window::GetHeight(),
    					  0.0f,
    					  mNear,
    					  mFar);

    return glm::perspective(glm::radians(mFov),
    						Window::GetAspectRatio(),
    						mNear, mFar);
}

glm::mat4 Xeno::CameraComponent::GetView() const
{
    return lookAt(GetTransform().GetPosition(),
                  GetTransform().GetPosition() + GetTransform().GetForward(),
                  GetTransform().GetUp());
}

void Xeno::CameraComponent::SetFov(const float fov)
{
    mFov = fov;
}

float Xeno::CameraComponent::GetFov() const
{
    return mFov;
}

void Xeno::CameraComponent::SetNear(const float nearPlane)
{
    mNear = nearPlane;
}

float Xeno::CameraComponent::GetNear() const
{
    return mNear;
}

void Xeno::CameraComponent::SetFar(const float farPlane)
{
    mFar = farPlane;
}