#pragma once

#include "Core/Core.h"

#include <glm/vec2.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <cstdint>

namespace Xeno
{
	// @brief Class to abstract SDL inputs.
	class XENO_API Input
	{
	public:
		~Input();

		enum class AxisType
		{
			MOUSE,
			JOYSTICK
		};

		// @brief Gets the key state.
		// @return bool: True if key is pressed, else false.
		static bool GetKey(SDL_Scancode code);
		// @brief Returns true during the frame the user starts pressing down the key.
		// @return bool: True if key is pressed, else false.
		static bool GetKeyDown(SDL_Scancode code);
		// @brief Returns true during the frame the user releases the key.
		// @return bool: True if key is released, else false.
		static bool GetKeyUp(SDL_Scancode code);
		// @brief Gets the current mouse mPosition on the screen.
		// @return glm::vec2: The mouse x and y mPosition.
		static glm::vec2 GetAxis(AxisType type);

	private:
		// @brief Default constructor.
		Input();

		// @brief Updates keyboard status.
		void Update();
		void ProcessEvents(const SDL_Event& event);

		// @brief Stores the current keyboard state.
		static inline const uint8_t* mKeyboardState;
		// @brief Stores the last keyboard state.
		static inline uint8_t* mPrevKeyboardState;
		// @brief Number of valid keys.
		static inline int mNumKeys;
		// @brief Current mouse state.
		static inline uint32_t mMouseState;
		// @brief Previous mouse state.
		static inline uint32_t mPrevMouseState;
		// @brief Stores the value of the mouse axis.
		static inline glm::vec2 mMouseAxis;
		// @brief Stores the value of the joystick axis.
		static inline glm::vec2 mJoystickAxis;

		friend class Application;
	};
}