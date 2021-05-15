#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
	:currentTime(0), maxTime(0)
{}

Timer::Timer(float max_time)
	:currentTime(0), maxTime(max_time)
{}

void Timer::Update(const float dt)
{
	currentTime += dt;
}

void Timer::Reset()
{
	currentTime = 0;
}

bool Timer::Ready()
{
	if (currentTime >= maxTime) {
		currentTime = 0;
		return true;
	}
	else return false;
}
