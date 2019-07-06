#pragma once
#include <functional>
#include "engine/sprite.h"

class CBullet : public DxEngine::CSprite
{
public:
	CBullet(const std::string& vImageFile) : DxEngine::CSprite(vImageFile) {}
	~CBullet() = default;

private:
	double	_Speed = 0.0;

	std::function<void(CBullet*)> _MoveFunc;

	friend class CBarragePattern;
	friend class CMovePattern;
	friend class CBarrageManager;
};