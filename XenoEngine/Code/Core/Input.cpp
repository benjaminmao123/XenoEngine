#include "pch.h"
#include "Input.h"
#include "Core/Time.h"

Xeno::Input::Input()
{
	sKeyboardState = SDL_GetKeyboardState(&sNumKeys);
	sPrevKeyboardState = new uint8_t[sNumKeys];
	memcpy(sPrevKeyboardState, sKeyboardState, sNumKeys);
}

Xeno::Input::~Input()
{
	delete[] sPrevKeyboardState;
}

bool Xeno::Input::GetKey(const KeyCode code)
{
	return sKeyboardState[(uint8_t)code];
}

bool Xeno::Input::GetKeyDown(const KeyCode code)
{
	return !sPrevKeyboardState[(uint8_t)code] && sKeyboardState[(uint8_t)code];
}

bool Xeno::Input::GetKeyUp(const KeyCode code)
{
	return sPrevKeyboardState[(uint8_t)code] && !sKeyboardState[(uint8_t)code];
}

glm::vec2 Xeno::Input::GetAxis(const AxisType type)
{
	switch (type)
	{
	case AxisType::MOUSE:
		return sMouseAxis;
	case AxisType::JOYSTICK:
		return sJoystickAxis;
	default:
		break;
	}

	return glm::vec2(0.0f, 0.0f);
}

const glm::vec2& Xeno::Input::GetMouseScrollDelta()
{
	return sMouseScrollDelta;
}

void Xeno::Input::SetCursorLockState(const CursorLockState state)
{
	sCursorLockState = state;

	switch (sCursorLockState)
	{
	case CursorLockState::LOCKED:
		SDL_SetRelativeMouseMode(SDL_TRUE);
		break;
	default:
		SDL_SetRelativeMouseMode(SDL_FALSE);
		break;
	}
}

void Xeno::Input::ProcessEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		sMouseAxis.x = event.motion.xrel;
		sMouseAxis.y = event.motion.yrel;
		break;
	case SDL_JOYAXISMOTION:
		sJoystickAxis.x = event.motion.xrel;
		sJoystickAxis.y = event.motion.yrel;
		break;
	case SDL_MOUSEWHEEL:
		sMouseScrollDelta.x = event.wheel.x;
		sMouseScrollDelta.y = event.wheel.y;
		break;
	default:
		break;
	}
}

void Xeno::Input::Update()
{
	memcpy(sPrevKeyboardState, sKeyboardState, sNumKeys);
	sMouseAxis = glm::vec2(0.0f, 0.0f);
	sMouseScrollDelta = glm::vec<2, int32_t>(0, 0);
}
