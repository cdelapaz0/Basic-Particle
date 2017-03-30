#include "Particle.h"
#include "Utilities.h"

//void Particle::Initialize(const EmitterAttributes & _attribs)
//{
//	lifeTime = Random::NextFloat(_attribs.minLifeTime, _attribs.maxLifeTime);
//
//	currSize = _attribs.startSize;
//	currColor = _attribs.startColor;
//	currVelocity = _attribs.startVelocity;
//
//	aliveTime = 0;
//	isAlive = true;
//}
//
//bool Particle::Update(float _fdt, const EmitterAttributes & _attribs)
//{
//	if (isAlive) 
//	{
//		aliveTime += _fdt;
//		if (aliveTime >= lifeTime)
//		{
//			isAlive = false;
//		}
//
//		float ratio = aliveTime / lifeTime;
//
//		currColor = Color::Lerp(_attribs.startColor, _attribs.endColor, ratio);
//		currVelocity = Vector3::Lerp(_attribs.startVelocity, _attribs.endVelocity, ratio);
//		currSize = Math::Lerp(_attribs.startSize, _attribs.endSize, ratio);
//	}
//	return isAlive;
//}
