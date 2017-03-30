#include "ParticleEmitter.h"
#include "Utilities.h"

#include <algorithm>
using std::sort;
using std::begin;
using std::end;

bool compLifeGreater(const Particle& a, const Particle& b)
{
	return a.lifeTime > b.lifeTime;
}

ParticleEmitter::ParticleEmitter()
{

}

void ParticleEmitter::Initialize(unsigned int NumParticles, float startS, float endS, Color startCol, Color endCol, Vector3 startV, Vector3 endV, Vector3 pos, float minLT, float maxLT)
{
	particles.resize(NumParticles);
	MaxParticles = NumParticles;

	worldMatrix = Matrix::Identity;

	SetSizeRange(startS, endS);
	SetColorRange(startCol,endCol);
	SetVelocity(startV, endV);
	SetPosition(pos);
	SetLifeTime(minLT, maxLT);
}

void ParticleEmitter::Update(float _fdt)
{
	elapsedTime += _fdt;
	if (elapsedTime >= spawnInterval)
	{
		elapsedTime = 0;
		unsigned int index = aliveCount;
		if (index < MaxParticles)
		{
			particles[index].alive = true;
			particles[index].lifeTime = Random::NextFloat(minLifeTime, maxLifeTime);
			particles[index].totalLifeTime = particles[index].lifeTime;
			particles[index].rot = 0;
			particles[index].velocity = Vector3::Zero;

			particles[index].vert.color = startColor;
			particles[index].vert.size = startSize;
			particles[index].vert.position = worldMatrix.Translation();
			aliveCount++;
		}
	}


	unsigned int currAliveCount = aliveCount;
	for (unsigned int i = 0; i < aliveCount; ++i)
	{
		particles[i].lifeTime -= _fdt;
		if (particles[i].lifeTime <= 0)
		{
			particles[i].lifeTime = 0;
			particles[i].alive = false;
			currAliveCount--;
			continue;
		}

		float r = particles[i].lifeTime / particles[i].totalLifeTime;

		particles[i].vert.color = Color::Lerp(startColor, endColor, r);
		particles[i].velocity = Vector3::Lerp(startVelocity, endVelocity, r);
		particles[i].vert.size = Math::Lerp(startSize, endSize, r);

		Vector3 pos = particles[i].vert.position + (particles[i].velocity * _fdt);
		particles[i].vert.position = pos;
	}

	//sort
	sort(particles.begin(), particles.begin() + aliveCount, compLifeGreater);
}

void ParticleEmitter::SetSizeRange(float startS, float endS)
{
	startSize = startS;
	endSize = endS;
}

void ParticleEmitter::SetColorRange(Color startCol, Color endCol)
{
	startColor = startCol;
	endColor = endCol;
}

void ParticleEmitter::SetVelocity(Vector3 startV, Vector3 endV)
{
	startVelocity = startV;
	endVelocity = endV;
}

void ParticleEmitter::SetPosition(Vector3 pos)
{
	worldMatrix.Translation(pos);
}

void ParticleEmitter::SetLifeTime(float minLT, float maxLT)
{
	minLifeTime = minLT;
	maxLifeTime = maxLT;
}
