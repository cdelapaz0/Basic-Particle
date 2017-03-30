#pragma once

#include "DXTKInclude.h"
#include "Particle.h"
#include <vector>
using std::vector;

/// Possible Solution to sort inefficiency
// 1. Circular Queue w/Smart insert
// 2. Object Pool of dead particles

class ParticleEmitter
{
public:
	ParticleEmitter();

	void Initialize(unsigned int NumParticles, float startS, float endS,
					Color startCol, Color endCol, Vector3 startV, Vector3 endV, 
					Vector3 pos, float minLT, float maxLT);

	void Update(float _fdt);

	void SetSizeRange(float startS, float endS);
	void SetColorRange(Color startCol, Color endCol);
	void SetVelocity(Vector3 startV, Vector3 endV);
	void SetPosition(Vector3 pos);
	void SetLifeTime(float minLT, float maxLT);

private:
	// TODO: Add particle list
	unsigned int aliveCount = 0;
	unsigned int MaxParticles;

	float spawnInterval = 1.0f;
	float elapsedTime = 0;

	vector<Particle> particles;
	
	Matrix worldMatrix;
	// TODO: Add Emission bounds


	// TODO: Make flyweight struct
	float startSize;
	float endSize;

	Color startColor;
	Color endColor;

	Vector3 startVelocity;
	Vector3 endVelocity;

	float minLifeTime;
	float maxLifeTime;
};