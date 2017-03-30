#pragma once


class sxTimer
{
public:
	sxTimer();

	void Reset();

	void Update();

	float GetDeltaTime();

	float GetTotalTime();

private:
	float deltaTime;
	float totalTime;
};