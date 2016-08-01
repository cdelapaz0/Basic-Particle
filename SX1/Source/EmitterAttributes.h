#pragma once

#include "DXTKInclude.h"

struct EmitterAttributes
{
	float minLifeTime;
	float maxLifeTime;

	float startSize;
	float endSize;

	Color startColor;
	Color endColor;

	Vector3 startVelocity;
	Vector3 endVelocity;
};