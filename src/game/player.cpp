#include "stdafx.h"
#include "player.h"
#include "engine/inputManager.h"
#include "engine/jsonUtil.h"
#include "common.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CPlayer::updateV(double vDeltaTime)
{
	CSprite::updateV(vDeltaTime);

	__updatePlayerState();
	__updatePlayerPosition();
	__updateAnimation();
}

//*********************************************************************
//FUNCTION:
void CPlayer::__init(const std::string& vConfigFile)
{
	_ASSERTE(!vConfigFile.empty());

	CJsonReader JsonReader(vConfigFile);
	SPEED_HIGH = JsonReader.readFloat("speed_high");
	SPEED_LOW = JsonReader.readFloat("speed_low");
	_ASSERTE(SPEED_HIGH > 0 && SPEED_LOW > 0);

	m_PlayerAnm1 = JsonReader.readAnimation("player_anm_1");
	m_PlayerAnm2 = JsonReader.readAnimation("player_anm_2");

	m_pPlayerBg1 = JsonReader.readSprite("effect_sprite_1");
	m_pPlayerBg1->setAnchor(m_pPlayerBg1->getSize() / 2);
	this->addChild(m_pPlayerBg1);
	m_pPlayerBg2 = JsonReader.readSprite("effect_sprite_2");
	m_pPlayerBg2->setAnchor(m_pPlayerBg2->getSize() / 2);
	this->addChild(m_pPlayerBg2);

	this->setPriorToChildsHint();
}

//*********************************************************************
//FUNCTION:
void CPlayer::__updatePlayerState()
{
	m_State = PLAYER_STATE_IDLE;

	if (GET_KEY_STATE(KEY_INPUT_UP)) m_State |= PLAYER_STATE_MOVE_UP;
	else if (GET_KEY_STATE(KEY_INPUT_DOWN)) m_State |= PLAYER_STATE_MOVE_DOWN;

	if (GET_KEY_STATE(KEY_INPUT_LEFT)) m_State |= PLAYER_STATE_MOVE_LEFT;
	else if (GET_KEY_STATE(KEY_INPUT_RIGHT)) m_State |= PLAYER_STATE_MOVE_RIGHT;

	if (GET_KEY_STATE(KEY_INPUT_LSHIFT)) m_State |= PLAYER_STATE_LOW_SPEED;

	if (GET_KEY_STATE(KEY_INPUT_Z)) m_State |= PLAYER_STATE_SHOOTING;
}

//*********************************************************************
//FUNCTION:
void CPlayer::__updatePlayerPosition()
{
	m_Speed = {};

	if (m_State & PLAYER_STATE_MOVE_UP) m_Speed.y = -1;
	if (m_State & PLAYER_STATE_MOVE_DOWN) m_Speed.y = 1;
	if (m_State & PLAYER_STATE_MOVE_LEFT) m_Speed.x = -1;
	if (m_State & PLAYER_STATE_MOVE_RIGHT) m_Speed.x = 1;

	m_Speed.normalize();
	m_Speed = m_State & PLAYER_STATE_LOW_SPEED ? m_Speed * SPEED_LOW : m_Speed * SPEED_HIGH;

	_Position += m_Speed;

	int Offset = 20;
	_Position.x = clip<float>(_Position.x, BORDER_L + Offset, BORDER_R - Offset);
	_Position.y = clip<float>(_Position.y, BORDER_U + Offset, BORDER_D - Offset);

	m_pPlayerBg1->setPosition(_Position);
	m_pPlayerBg2->setPosition(_Position);
}

//*********************************************************************
//FUNCTION:
void CPlayer::__updateAnimation()
{
	if ((m_State & PLAYER_STATE_MOVE_LEFT) || (m_State & PLAYER_STATE_MOVE_RIGHT))
	{
		this->setImageFile(m_PlayerAnm2.ImageFile, m_PlayerAnm2.forward());
		m_PlayerAnm1.reset();
	}
	else
	{
		this->setImageFile(m_PlayerAnm1.ImageFile, m_PlayerAnm1.forward());
		m_PlayerAnm2.reset();
	}

	this->setAnchor(getSize() / 2);
	this->setFlip(m_State & PLAYER_STATE_MOVE_RIGHT);

	m_pPlayerBg1->setRotation(m_pPlayerBg1->getRotation() + 0.02);
	m_pPlayerBg1->setVisible(m_State & PLAYER_STATE_LOW_SPEED);
	m_pPlayerBg2->setRotation(m_pPlayerBg2->getRotation() + 0.04);
}