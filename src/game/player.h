#pragma once
#include "engine/sprite.h"

class CPlayer : public DxEngine::CSprite
{
public:
	CPlayer() { __init(); }
	~CPlayer() = default;

	void updateV(double vDeltaTime) override;

private:
	void __init();
};