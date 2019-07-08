#pragma once
#include <vector>
#include "engine/math.h"
#include "engine/sprite.h"

using namespace DxEngine;

struct SParticle
{
	DxEngine::CSprite* pSprite = nullptr;
	float SpeedX = 0.0;
	float SpeedY = 0.0;
};

class CParticle01 : public CNode
{
public:
	CParticle01(const recti& vArea, float vDensity);

	void updateV();

private:
	std::vector<SParticle> m_Particles;
	recti m_Area = {};
};