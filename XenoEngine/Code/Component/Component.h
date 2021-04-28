#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

namespace Xeno
{
	class Entity;
	class Transform;

	// @brief Base class for all components.
	class XENO_API Component : public NonCopyable
	{
	public:
		explicit Component(Entity* owner = nullptr);
		virtual ~Component() = 0;

		void SetEnabled(bool state);
		[[nodiscard]] bool IsEnabled() const;

		Transform& GetTransform();
		[[nodiscard]] const Transform& GetTransform() const;
		Entity* GetEntity();
		[[nodiscard]] const Entity* GetEntity() const;

	private:
		virtual void OnAwake();
		virtual void OnStart();
		virtual void OnUpdate();
		virtual void OnEnable();
		virtual void OnDisable();
		virtual void OnDestroy();

		Entity* mOwner;

		bool mIsEnabled = true;
		bool mIsAwakeCalled = false;
		bool mIsStartCalled = false;

		friend class Entity;
	};
}