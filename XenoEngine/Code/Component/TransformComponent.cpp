#include "pch.h"
#include "Component/TransformComponent.h"

#include <glm/gtx/matrix_decompose.hpp>

Xeno::TransformComponent::TransformComponent(Entity* owner) :
    Component(owner),
	mPosition(0.0f, 0.0f, 0.0f),
	mRotation(glm::vec3(0.0f, 0.0f, 0.0f)),
	mScale(1.0f, 1.0f, 1.0f)
{ }

void Xeno::TransformComponent::Translate(const glm::vec3& translation)
{
	mPosition += translation;
}

void Xeno::TransformComponent::Translate(const float x, const float y, const float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

void Xeno::TransformComponent::Rotate(const glm::vec3& eulers, const Space space)
{
	const glm::quat rot = glm::quat(radians(eulers));

	switch (space)
	{
	case Space::SELF:
		mRotation *= rot;
		break;
	case Space::WORLD:
		mRotation = rot * mRotation;
		break;
	default:
		break;
	}
}

void Xeno::TransformComponent::Rotate(const float x, const float y, const float z, const Space space)
{
	Rotate(glm::vec3(x, y, z), space);
}

void Xeno::TransformComponent::Rotate(const glm::vec3& axis, const float angle, const Space space)
{
	const glm::quat rot = angleAxis(glm::radians(angle), axis);

	switch (space)
	{
	case Space::SELF:
		mRotation *= rot;
		break;
	case Space::WORLD:
		mRotation = rot * mRotation;
		break;
	default:
		break;
	}
}

void Xeno::TransformComponent::SetPosition(const glm::vec3& position)
{
	mPosition = position;
}

void Xeno::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	SetPosition({x, y, z});
}

glm::vec3& Xeno::TransformComponent::GetPosition()
{
	return mPosition;
}

const glm::vec3& Xeno::TransformComponent::GetPosition() const
{
	return mPosition;
}

void Xeno::TransformComponent::SetRotation(const glm::quat& rotation)
{
	mRotation = rotation;
}

void Xeno::TransformComponent::SetRotationEuler(const glm::vec3& eulers)
{
	mRotation = glm::quat(radians(eulers));
}

void Xeno::TransformComponent::SetRotationEuler(const float x, const float y, const float z)
{
	SetRotationEuler({x, y, z});
}

const glm::quat& Xeno::TransformComponent::GetRotation() const
{
	return mRotation;
}

glm::vec3 Xeno::TransformComponent::GetRotationEuler() const
{
	return glm::vec3(eulerAngles(mRotation));
}

void Xeno::TransformComponent::SetScale(const glm::vec3& scale)
{
	mScale = scale;
}

void Xeno::TransformComponent::SetScale(const float x, const float y, const float z)
{
	SetScale({x, y, z});
}

glm::vec3 Xeno::TransformComponent::GetScale() const
{
	return mScale;
}

glm::vec3 Xeno::TransformComponent::GetForward() const
{
	return inverse(mRotation) * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Xeno::TransformComponent::GetRight() const
{
	return inverse(mRotation) * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Xeno::TransformComponent::GetUp() const
{
	return inverse(mRotation) * glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Xeno::TransformComponent::GetModelMatrix() const
{
	glm::mat4 model(1.0f);

	const glm::mat4 translate = glm::translate(model, mPosition);
	const glm::mat4 rotate = toMat4(mRotation);
	const glm::mat4 scale = glm::scale(model, mScale);

	model = translate * rotate * scale;

	return model;
}

Xeno::TransformComponent& Xeno::TransformComponent::operator*=(const TransformComponent& rhs)
{
	const glm::mat4 model = GetModelMatrix() * rhs.GetModelMatrix();

	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 skew;
	glm::vec4 perspective;

	decompose(model, scale, rotation, translation, skew, perspective);

	Translate(translation);
	Rotate(eulerAngles(rotation));
	SetScale(scale);

	return *this;
}
