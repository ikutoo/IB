#pragma once
#include <functional>
#include "engine/sprite.h"

using namespace DxEngine;

class CBullet : public CSprite
{
public:
	CBullet(const std::string& vImageFile, const recti& vRect = {});
	~CBullet() = default;

	void setOwn2Player(bool vValue) { m_IsOwn2Player = vValue; }
	bool isOwn2Player()  const { return m_IsOwn2Player; }

private:
	double	_Speed = 0.0;

	std::function<void(CBullet*)> _MoveFunc;

	bool m_IsOwn2Player = false;

	friend class CBarragePattern;
	friend class CMovePattern;
	friend class CBarrageManager;
};