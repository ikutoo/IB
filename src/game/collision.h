#pragma once
#include "engine/math.h"

using namespace DxEngine;

class CCollisionDetector
{
public:
	CCollisionDetector();
	~CCollisionDetector();

	void detectCollision(vec2f vPlayerPosition, int vGraphHandle);

	bool isPlayerHit() const { return m_IsPlayerHit; }
	bool isPlayerGrazed() const { return m_IsPlayerGrazed; }

private:
	int m_BarrageSoftImage = -1;

	bool m_IsPlayerHit = false;
	bool m_IsPlayerGrazed = false;
};