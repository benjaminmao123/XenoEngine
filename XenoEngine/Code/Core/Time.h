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

		void Init();

		// @brief Updates delta time.
		void Update();

		// @brief The time of the last frame.
		uint64_t mLastFrameTime = 0;
		uint64_t mElapsedTime = 0;
		// @brief The time between the last frame and
		// the current frame.
		static inline float sDeltaTime = 0.0f;

		friend class Application;
    };
}