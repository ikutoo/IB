#pragma once
#include <functional>
#include "sprite.h"

class CBullet : public DxEngine::CSprite
{
public:
	CBullet();
	~CBullet();

private:
	double	_Angle = 0.0;
	double	_Speed = 0.0;
	int		_BulletType = -1;

	std::function<void(CBullet*)> _MoveFunc;

	friend class CBarragePattern;
	friend class CMovePattern;
	friend class CBarrageManager;
};