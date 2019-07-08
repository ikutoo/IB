#pragma once
#include <functional>
#include "engine/sprite.h"

using namespace DxEngine;

class CBullet : public CSprite
{
public:
	CBullet(const std::string& vImageFile, const recti& vRect = {}) :CSprite(vImageFile, vRect) {}
	~CBullet() = default;

private:
	double	_Speed = 0.0;

	std::function<void(CBullet*)> _MoveFunc;

	friend class CBarragePattern;
	friend class CMovePattern;
	friend class CBarrageManager;
};