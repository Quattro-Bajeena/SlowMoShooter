#pragma once
class Timer
{
	float currentTime;
	float maxTime;

public:
	Timer();
	Timer(float max_time);
	void Update(const float dt);
	void Reset();
	bool Ready();
};

