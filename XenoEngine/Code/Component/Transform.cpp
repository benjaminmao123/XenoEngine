#include "pch.h"
#include "Transform.h"

#include <glm/gtx/matrix_decompose.hpp>

Xeno::Transform::Transform(Entity* owner) :
    Component(owner),
	mPosition(0.0f, 0.0f, 0.0f),
	mRotation(glm::vec3(0.0f, 0.0f, 0.0f)),
	mScale(1.0f, 1.0f, 1.0f)
{ }

void Xeno::Transform::Translate(const glm::vec3& translation)
{
	mPosition += translation;
}

void Xeno::Transform::Translate(const float x, const float y, const float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

void Xeno::Transform::Rotate(const glm::vec3& eulers, const Space space)
{
	const glm::quat rot = glm::quat(glm::radians(eulers));

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

void Xeno::Transform::Rotate(const float x, const float y, const float z, const Space space)
{
	Rotate(glm::vec3(x, y, z), space);
}

void Xeno::Transform::Rotate(const glm::vec3& axis, const float angle, const Space space)
{
	const glm::quat rot = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

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

void Xeno::Transform::SetPosition(const glm::vec3& position)
{
	mPosition = position;
}

void Xeno::Transform::SetPosition(const float x, const float y, const float z)
{
	SetPosition({ x, y, z });
}

glm::vec3& Xeno::Transform::GetPosition()
{
	return mPosition;
}

const glm::vec3& Xeno::Transform::GetPosition() const
{
	return mPosition;
}

void Xeno::Transform::SetRotation(const glm::quat& rotation)
{
	mRotation = rotation;
}

void Xeno::Transform::SetRotationEuler(const glm::vec3& eulers)
{
	mRotation = glm::quat(glm::radians(eulers));
}

void Xeno::Transform::SetRotationEuler(const float x, const float y, const float z)
{
	SetRotationEuler({ x, y, z });
}

const glm::quat& Xeno::Transform::GetRotation() const
{
	return mRotation;
}

glm::vec3 Xeno::Transform::GetRotationEuler() const
{
	return glm::vec3(glm::eulerAngles(mRotation));
}

void Xeno::Transform::SetLocalRotation(const glm::quat& rotation)
{
	mLocalRotation = rotation;
}

void Xeno::Transform::SetLocalRotationEuler(const glm::vec3& eulers)
{
	mLocalRotation = glm::quat(glm::radians(eulers));
}

void Xeno::Transform::SetLocalRotationEuler(const float x, const float y, const float z)
{
	SetLocalRotationEuler({ x, y, z });
}

const glm::quat& Xeno::Transform::GetLocalRotation() const
{
	return mLocalRotation;
}

glm::vec3 Xeno::Transform::GetLocalRotationEuler() const
{
	return glm::vec3(glm::eulerAngles(mLocalRotation));
}

void Xeno::Transform::SetScale(const glm::vec3& scale)
{
	mScale = scale;
}

void Xeno::Transform::SetScale(const float x, const float y, const float z)
{
	SetScale({x, y, z});
}

glm::vec3 Xeno::Transform::GetScale() const
{
	return mScale;
}

glm::vec3 Xeno::Transform::GetForward() const
{
	return glm::inverse(mRotation) * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Xeno::Transform::GetRight() const
{
	return glm::inverse(mRotation) * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Xeno::Transform::GetUp() const
{
	return glm::inverse(mRotation) * glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Xeno::Transform::GetModelMatrix() const
{
	glm::mat4 model(1.0f);

	const glm::mat4 translate = glm::translate(model, mPosition);
	const glm::mat4 rotate = glm::toMat4(mRotation);
	const glm::mat4 scale = glm::scale(model, mScale);

	model = translate * rotate * scale;

	return model;
}

Xeno::Transform& Xeno::Transform::operator*=(const Transform& rhs)
{
	const glm::mat4 model = GetModelMatrix() * rhs.GetModelMatrix();

	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(model, scale, rotation, translation, skew, perspective);

	Translate(translation);
	Rotate(glm::eulerAngles(rotation));
	SetScale(scale);

	return *this;
}
