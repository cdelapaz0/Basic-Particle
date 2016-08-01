#pragma once
#include "DXTKInclude.h"
#include "EmitterAttributes.h"

class Particle
{
public:
	void Initialize(const EmitterAttributes& _attribs);
	bool Update(float _fdt, const EmitterAttributes& _attribs);

private:
	float aliveTime;
	float lifeTime;

	float currSize;
	Color currColor;
	Vector3 currVelocity;

	bool isAlive;
};

