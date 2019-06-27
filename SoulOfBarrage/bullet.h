#pragma once
#include "sprite.h"

class CBullet : public DxEngine::CSprite
{
public:
	CBullet();
	~CBullet();

private:
	double m_Angle = 0.0;
	double m_Speed = 0.0;
	int m_BulletType = -1;
	int m_MovePattern = -1;
};