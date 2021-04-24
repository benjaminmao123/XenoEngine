#pragma once

#include "Core/Core.h"
#include "Utility/NonCopyable.h"
#include "Core/KeyCodes.h"

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <cstdint>

namespace Xeno
{
    // @brief Class to abstract SDL inputs.
    class XENO_API Input : public NonCopyable
    {
    public:
        enum class AxisType
        {
            MOUSE,
            JOYSTICK
        };

        ~Input();

        // @brief Gets the key state.
        // @return bool: True if key is pressed, else false.
        static bool GetKey(KeyCode code);
        // @brief Returns true during the frame the user starts pressing down the key.
        // @return bool: True if key is pressed, else false.
        static bool GetKeyDown(KeyCode code);
        // @brief Returns true during the frame the user releases the key.
        // @return bool: True if key is released, else false.
        static bool GetKeyUp(KeyCode code);
        // @brief Gets the current mouse mPosition on the screen.
        // @return glm::vec2: The mouse x and y mPosition.
        static glm::vec2 GetAxis(AxisType type);
        static const glm::vec2& GetMouseScrollDelta();

    private:
        // @brief Default constructor.
        Input();

        void ProcessEvents(const SDL_Event& event);
        // @brief Updates keyboard status.
        void Update();

        // @brief Stores the current keyboard state.
        static inline const uint8_t* sKeyboardState;
        // @brief Stores the last keyboard state.
        static inline uint8_t* sPrevKeyboardState;
        // @brief Number of valid keys.
        static inline int sNumKeys;
        // @brief Current mouse state.
        static inline uint32_t sMouseState;
        // @brief Previous mouse state.
        static inline uint32_t sPrevMouseState;
        // @brief Stores the value of the mouse axis.
        static inline glm::vec<2, int32_t> sMouseAxis;
        // @brief Stores the value of the joystick axis.
        static inline glm::vec<2, int32_t> sJoystickAxis;
        static inline glm::vec<2, int32_t> sMouseScrollDelta;

        friend class Application;
    };
}