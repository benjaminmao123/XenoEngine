#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Xeno
{
	// @brief Class providing the mPosition, mScale, and mRotation of
	// an object.
	class XENO_API TransformComponent : public NonCopyable
	{
	public:
		// @brief Defines the Space in which operations are performed.
		enum class Space
		{
			WORLD,
			SELF
		};

		// @brief Default constructor.
	    explicit TransformComponent();

		// @brief Changes the mPosition by given offsets.
		// @param const glm::vec3& translation: Amount to offset the mPosition.
		void Translate(const glm::vec3& translation);
		// @brief Changes the mPosition by given offsets.
		// @param float x: The x offset.
		// @param float y: The y offset.
		// @param float z: The z offset.
		void Translate(float x, float y, float z);

		// @brief Rotates the TransformComponent in euler angles.
		// @param const glm::vec3& eulers: The angles to rotate by in eulers.
		// @param Space space: The space in which to rotate.
		void Rotate(const glm::vec3& eulers, Space space = Space::SELF);
		// @brief Rotates the TransformComponent in euler angles.
		// @param float x: The x amount to rotate in eulers.
		// @param float y: The y amount to rotate in eulers.
		// @param float z: The z amount to rotate in eulers.
		// @param Space space: The space in which to rotate.
		void Rotate(float x, float y, float z, Space space = Space::SELF);
		// @brief Rotates the TransformComponent from the given axis and angle.
		// @param const glm::vec3& axis: The axes on which to rotate.
		// @param float angle: The amount to rotate in eulers.
		// @param Space space: The space in which to rotate.
		void Rotate(const glm::vec3& axis, float angle, Space space = Space::SELF);

		// @brief Sets the mPosition of the TransformComponent.
		// @param const glm::vec3&: The mPosition to set the TransformComponent.
		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		// @brief Gets the mPosition of the TransformComponent.
		// @return const glm::vec3&: The mPosition of the TransformComponent.  
		glm::vec3& GetPosition();
		// @brief Gets the mPosition of the TransformComponent.
		// @return const glm::vec3&: The mPosition of the TransformComponent.  
		[[nodiscard]] const glm::vec3& GetPosition() const;

		// @brief Sets the mRotation of the TransformComponent through quaternion.
		// @param const glm::quat& mRotation: The mRotation to set the TransformComponent.
		void SetRotation(const glm::quat& rotation);
		// @brief Sets the mRotation of the TransformComponent in eulers.
		// @param const glm::vec3& eulers: The mRotation to set the TransformComponent.
		void SetRotationEuler(const glm::vec3& eulers);
		void SetRotationEuler(float x, float y, float z);
		// @brief Gets the mRotation of the TransformComponent as a quaternion.
		// @return const glm::quat&: The mRotation of the TransformComponent.
		[[nodiscard]] const glm::quat& GetRotation() const;
		// @brief Gets the mRotation of the TransformComponent as eulers.
		// @return const glm::vec3: The mRotation of the TransformComponent.		
		[[nodiscard]] glm::vec3 GetRotationEuler() const;

		// @brief Sets the mScale of the TransformComponent.
		// @param const glm::vec3& mScale: The factors to set the mScale.
		void SetScale(const glm::vec3& scale);
		void SetScale(float x, float y, float z);
		// @brief Gets the mScale of the TransformComponent.
		// @return glm::vec3: The mScale of the TransformComponent.
		[[nodiscard]] glm::vec3 GetScale() const;

		// @brief Gets the forward direction of the TransformComponent.
		// @return glm::vec3: The forward direction of the TransformComponent.
		[[nodiscard]] glm::vec3 GetForward() const;
		// @brief Gets the right direction of the TransformComponent.
		// @return glm::vec3: The right direction of the TransformComponent.
		[[nodiscard]] glm::vec3 GetRight() const;
		// @brief Gets the up direction of the TransformComponent.
		// @return glm::vec3: The up direction of the TransformComponent.
		[[nodiscard]] glm::vec3 GetUp() const;

		[[nodiscard]] glm::mat4 GetModelMatrix() const;

		TransformComponent& operator*=(const TransformComponent& rhs);

	private:
		// @brief Stores the mPosition of the TransformComponent.
		glm::vec3 mPosition;
		// @brief Stores the mRotation of the TransformComponent.
		glm::quat mRotation;
		// @brief Stores the mScale of the TransformComponent.
		glm::vec3 mScale;
	};
}