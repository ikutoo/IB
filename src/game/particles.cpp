#include "stdafx.h"
#include "particles.h"

//*********************************************************************
//FUNCTION:
CParticle01::CParticle01(const recti& vArea, float vDensity) : m_Area(vArea)
{
	int Num = 0.0001 * vArea.w * vArea.h * vDensity;

	for (int i = 0; i < Num; ++i)
	{
		CSprite* pParticle = new CSprite("particle_00.png");
		pParticle->setScale(0.3 + 0.3 * randf(), 0.3 + 0.3 * randf());
		pParticle->setBrightness(vec3i{ 100 + rand() % 50, 100 + rand() % 50, 0 });
		float PosX = rand() % vArea.w + vArea.x;
		float PosY = rand() % vArea.h + vArea.y + vArea.h;
		pParticle->setPosition(vec2f{ PosX, PosY });

		float SpeedX = -0.2 + 0.4 * randf();
		float SpeedY = -0.3 - 0.2 * randf();

		m_Particles.emplace_back(SParticle{ pParticle, SpeedX, SpeedY });
		this->addChild(pParticle);
	}
}

//*********************************************************************
//FUNCTION:
void CParticle01::update()
{
	for (auto pParticle : m_Particles)
	{
		if (_Counter % 100 == 0) pParticle.SpeedX = -0.2 + 0.4 * randf();

		float PosX = pParticle.pSprite->getPosition().x + pParticle.SpeedX;
		float PosY = pParticle.pSprite->getPosition().y + pParticle.SpeedY;

		if (PosY < m_Area.y) { PosX = rand() % m_Area.w + m_Area.x; PosY = m_Area.y + m_Area.h; };

		if (PosX < m_Area.x) PosX = m_Area.x + m_Area.w;
		else if (PosX > m_Area.x + m_Area.w) PosX = m_Area.x;

		pParticle.pSprite->setPosition(PosX, PosY);
	}
}