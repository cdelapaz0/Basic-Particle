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
					Vector3 pos, float minLT, float maxLT, float spawnI, 
					unsigned int spawnCount, float spawnW, float spawnH);

	void Update(float _fdt);

	// Particle Properties
	void SetParticleSizeRange(float startS, float endS);
	void SetParticleColorRange(Color startCol, Color endCol);
	void SetParticleVelocityRange(Vector3 startV, Vector3 endV);
	void SetParticleLifeTimeRange(float minLT, float maxLT);

	// Emitter Properties
	void SetPosition(Vector3 pos);
	void SetSpawnInterval(float spawnI);
	void SetSpawnCount(float spawnCount);
	void SetSpawnBounds(float width, float height);

	const Matrix& GetWorldMatrix();
	unsigned int  GetMaxParticleCount();
	unsigned int  GetAliveCount();

	ParticleVertex* GetVertexArray();
	unsigned int	GetVertexArraySize();

private:
	Matrix					worldMatrix;

	vector<Particle>		particles;
	vector<ParticleVertex>	verts;

	unsigned int			aliveCount;
	unsigned int			maxParticlesCount;

	float					spawnInterval;
	unsigned int			spawnAmount;
	float					elapsedTime;

	float					boundWidth;
	float					boundHeight;

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