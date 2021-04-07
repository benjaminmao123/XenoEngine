#include "pch.h"
#include "Core/Time.h"

#include <SDL2/SDL_timer.h>

void Xeno::Time::Init()
{
	mElapsedTime = SDL_GetPerformanceCounter();
}

void Xeno::Time::Update()
{
	mLastFrameTime = mElapsedTime;
	mElapsedTime = SDL_GetPerformanceCounter();
	sDeltaTime = static_cast<float>((mElapsedTime - mLastFrameTime) * 1000.0f /
        static_cast<float>(SDL_GetPerformanceFrequency())) * 0.001f;
}

float Xeno::Time::GetDeltaTime()
{
	return sDeltaTime;
}