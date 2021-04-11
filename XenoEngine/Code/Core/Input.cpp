#include "pch.h"
#include "Core/Input.h"
#include "Core/Time.h"

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

Xeno::Input::Input()
{
	sKeyboardState = SDL_GetKeyboardState(&sNumKeys);
	sPrevKeyboardState = new uint8_t[sNumKeys];
	memcpy(sPrevKeyboardState, sKeyboardState, sNumKeys);
}

void Xeno::Input::Update()
{
	memcpy(sPrevKeyboardState, sKeyboardState, sNumKeys);
	sMouseAxis = glm::vec2(0.0f, 0.0f);
}

void Xeno::Input::ProcessEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		sMouseAxis.x = event.motion.xrel * Time::GetDeltaTime();
		sMouseAxis.y = event.motion.yrel * Time::GetDeltaTime();
		break;
	case SDL_JOYAXISMOTION:
		sJoystickAxis.x = event.motion.xrel;
		sJoystickAxis.y = event.motion.yrel;
		break;
	default:
		break;
	}
}