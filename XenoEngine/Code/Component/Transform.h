#pragma once

#include "Core/Core.h"
#include "Component/Component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Xeno
{
	class XENO_API Transform final : public Component
	{
	public:
		enum class Space
		{
			WORLD,
			SELF
		};

	    explicit Transform(Entity* owner = nullptr);

		void Translate(const glm::vec3& translation);
		void Translate(float x, float y, float z);

		void Rotate(const glm::vec3& eulers, Space space = Space::SELF);
		void Rotate(float x, float y, float z, Space space = Space::SELF);
		void Rotate(const glm::vec3& axis, float angle, Space space = Space::SELF);

		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		glm::vec3& GetPosition();
		[[nodiscard]] const glm::vec3& GetPosition() const;

		void SetRotation(const glm::quat& rotation);
		void SetRotationEuler(const glm::vec3& eulers);
		void SetRotationEuler(float x, float y, float z);
		[[nodiscard]] const glm::quat& GetRotation() const;		
		[[nodiscard]] glm::vec3 GetRotationEuler() const;

		void SetScale(const glm::vec3& scale);
		void SetScale(float x, float y, float z);
		[[nodiscard]] glm::vec3 GetScale() const;

		[[nodiscard]] glm::vec3 GetForward() const;
		[[nodiscard]] glm::vec3 GetRight() const;
		[[nodiscard]] glm::vec3 GetUp() const;

		[[nodiscard]] glm::mat4 GetModelMatrix() const;

		Transform& operator*=(const Transform& rhs);

	private:
		glm::vec3 mPosition;
		glm::quat mRotation;
		glm::vec3 mScale;
	};
}