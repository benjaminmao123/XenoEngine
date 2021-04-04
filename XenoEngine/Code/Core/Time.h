#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"

#include <cstdint>

namespace Xeno
{
    class XENO_API Time : public NonCopyable
    {
	public:
		// @brief Gets the time between the last frame 
		// and the current frame.
		static float GetDeltaTime();

	private:
		// @brief Default constructor.
		Time() = default;

		// @brief Updates delta time.
		void Update();

		// @brief The time of the last frame.
		uint32_t mLastFrameTime = 0;
		uint64_t mElapsedTime = 0;
		// @brief The time between the last frame and
		// the current frame.
		static float mDeltaTime;

		friend class Application;
    };
}