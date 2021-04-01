#include "pch.h"
#include "Input.h"

Xeno::Input::~Input()
{
	delete[] mPrevKeyboardState;
}

bool Xeno::Input::GetKey(const SDL_Scancode code)
{
	return mKeyboardState[code];
}

bool Xeno::Input::GetKeyDown(const SDL_Scancode code)
{
	return !mPrevKeyboardState[code] && mKeyboardState[code];
}

bool Xeno::Input::GetKeyUp(const SDL_Scancode code)
{
	return mPrevKeyboardState[code] && !mKeyboardState[code];
}

glm::vec2 Xeno::Input::GetAxis(const AxisType type)
{
	switch (type)
	{
	case AxisType::MOUSE:
		return mMouseAxis;
	case AxisType::JOYSTICK:
		return mJoystickAxis;
	default:
		break;
	}

	return glm::vec2(0.0f, 0.0f);
}

Xeno::Input::Input()
{
	mKeyboardState = SDL_GetKeyboardState(&mNumKeys);
	mPrevKeyboardState = new Uint8[mNumKeys];
	memcpy(mPrevKeyboardState, mKeyboardState, mNumKeys);
}

void Xeno::Input::Update()
{
	memcpy(mPrevKeyboardState, mKeyboardState, mNumKeys);
	mMouseAxis = glm::vec2(0.0f, 0.0f);
}

void Xeno::Input::ProcessEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		break;
	case SDL_JOYAXISMOTION:
		mJoystickAxis.x = event.motion.xrel;
		mJoystickAxis.y = event.motion.yrel;
		break;
	default:
		break;
	}
}