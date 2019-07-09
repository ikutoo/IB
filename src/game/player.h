#pragma once
#include <vector>
#include "engine/sprite.h"
#include "engine/animation.h"

using namespace DxEngine;

class CPlayer : public CSprite
{
	enum EPlayerState
	{
		PLAYER_STATE_IDLE = 0,
		PLAYER_STATE_MOVE_LEFT = 1,
		PLAYER_STATE_MOVE_RIGHT = 2,
		PLAYER_STATE_MOVE_UP = 4,
		PLAYER_STATE_MOVE_DOWN = 8,
		PLAYER_STATE_LOW_SPEED = 16,
		PLAYER_STATE_SHOOTING = 32
	};

public:
	CPlayer(const std::string& vConfigFile) { __init(vConfigFile); }
	~CPlayer() = default;

	void updateV(double vDeltaTime) override;

private:
	uint32_t m_State = PLAYER_STATE_IDLE;
	uint32_t m_AnmCounter = 0;

	vec2f m_Speed = {};

	SAnimation m_PlayerAnm1;
	SAnimation m_PlayerAnm2;

	CSprite* m_pPlayerBg1 = nullptr;
	CSprite* m_pPlayerBg2 = nullptr;

	float SPEED_HIGH = {};
	float SPEED_LOW = {};

	void __init(const std::string& vConfigFile);
	void __updatePlayerState();
	void __updatePlayerPosition();
	void __updateAnimation();
};