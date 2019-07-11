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
		PLAYER_STATE_SHOOTING = 32,
		PLAYER_STATE_GRAZE = 64
	};

public:
	CPlayer(const std::string& vConfigFile);
	~CPlayer();

	void updateV(double vDeltaTime) override;

	void shoot();
	void dead();
	void graze(bool IsGrazed);

	int getGrazeScore() const { return m_GrazeScore; };

private:
	uint32_t m_State = PLAYER_STATE_IDLE;

	vec2f m_Speed = {};

	SAnimation m_PlayerAnm1;	//自机高速移动动画
	SAnimation m_PlayerAnm2;	//自机低速移动动画

	CSprite* m_pPlayer = nullptr;
	CSprite* m_pPlayerBg1 = nullptr;
	CSprite* m_pPlayerBg2 = nullptr;

	float SPEED_HIGH = {};
	float SPEED_LOW = {};

	int m_GrazeScore = 0;

	int m_DeathProtectionCounter = 0;

	bool m_IsGrazed = false;

	int m_SoundHandleDead = -1;
	int m_SoundHandleGraze = -1;
	int m_SoundHandleShoot = -1;

	void __init(const std::string& vConfigFile);
	void __destroy();

	void __updatePlayerState();
	void __updatePlayerPosition();
	void __updateAnimation();
};