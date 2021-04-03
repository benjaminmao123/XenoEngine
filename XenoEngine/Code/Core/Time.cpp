#include "pch.h"
#include "Core/Time.h"

#include <SDL2/SDL_timer.h>

float Xeno::Time::mDeltaTime = 0.0f;

void Xeno::Time::Update()
{
	mElapsedTime = SDL_GetPerformanceCounter();
	mDeltaTime = static_cast<float>((mElapsedTime - mLastFrameTime) * 1000 /
									static_cast<float>(SDL_GetPerformanceFrequency()));
	mLastFrameTime = mElapsedTime;
}

float Xeno::Time::GetDeltaTime()
{
	return mDeltaTime;
}