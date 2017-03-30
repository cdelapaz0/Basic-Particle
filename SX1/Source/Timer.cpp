#include "Timer.h"


#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;


high_resolution_clock::time_point startTime;

high_resolution_clock::time_point prevTime;
high_resolution_clock::time_point currTime;

sxTimer::sxTimer()
{
	Reset();
}

void sxTimer::Reset()
{
	prevTime = currTime = startTime = high_resolution_clock::now();

	deltaTime = 0;
	totalTime = 0;
}

void sxTimer::Update()
{
	prevTime = currTime;
	currTime = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(currTime - startTime);
	totalTime = (float)time_span.count();

	time_span = duration_cast<duration<double>>(currTime - prevTime);
	deltaTime = (float)time_span.count();
}

float sxTimer::GetDeltaTime()
{
	return deltaTime;
}

float sxTimer::GetTotalTime()
{
	return totalTime;
}


