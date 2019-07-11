#include "stdafx.h"
#include "player.h"
#include <DXLib/DxLib.h>
#include "engine/inputManager.h"
#include "engine/jsonUtil.h"
#include "engine/resourceManager.h"
#include "common.h"
#include "barragePattern.h"
#include "barrageManager.h"

using namespace DxEngine;

const float INITIAL_POS_X = GRAPH_SIZE_X * 0.5;
const float INITIAL_POS_Y = 960;
const int	DEATH_PROTECTION_MAX_COUNT = 120;

//*********************************************************************
//FUNCTION:
CPlayer::CPlayer(const std::string& vConfigFile)
{
	__init(vConfigFile);
}

//*********************************************************************
//FUNCTION:
CPlayer::~CPlayer()
{
	__destroy();
}

//*********************************************************************
//FUNCTION:
void CPlayer::updateV(double vDeltaTime)
{
	CSprite::updateV(vDeltaTime);

	__updatePlayerState();
	__updatePlayerPosition();
	__updateAnimation();

	m_DeathProtectionCounter--;

	if (m_State & PLAYER_STATE_GRAZE) { CHECK_RESULT(DxLib::PlaySoundMem(m_SoundHandleGraze, DX_PLAYTYPE_LOOP)); }
	else { CHECK_RESULT(DxLib::StopSoundMem(m_SoundHandleGraze)); }

	if (m_State & PLAYER_STATE_SHOOTING) { shoot(); CHECK_RESULT(DxLib::PlaySoundMem(m_SoundHandleShoot, DX_PLAYTYPE_LOOP)); }
	else { CHECK_RESULT(DxLib::StopSoundMem(m_SoundHandleShoot)); }
}

//*********************************************************************
//FUNCTION:
void CPlayer::shoot()
{
	CBarrage* pBarrage = new CBarrage(CBarragePattern::playerBarrage00);
	pBarrage->setLiveTime(30);
	CBarrageManager::getInstance()->startBarrage(pBarrage, this);
}

//*********************************************************************
//FUNCTION:
void CPlayer::dead()
{
	if (m_DeathProtectionCounter > 0) { return; }
	m_DeathProtectionCounter = DEATH_PROTECTION_MAX_COUNT;

	this->setPosition(INITIAL_POS_X, INITIAL_POS_Y);

	CHECK_RESULT(DxLib::PlaySoundMem(m_SoundHandleDead, DX_PLAYTYPE_BACK));
}

//*********************************************************************
//FUNCTION:
void CPlayer::graze(bool IsGrazed)
{
	m_IsGrazed = IsGrazed;

	if (m_DeathProtectionCounter > 0) { return; }

	m_GrazeScore++;
}

//*********************************************************************
//FUNCTION:
void CPlayer::__init(const std::string& vConfigFile)
{
	_ASSERTE(!vConfigFile.empty());

	this->setPosition(INITIAL_POS_X, INITIAL_POS_Y);

	CJsonReader JsonReader(vConfigFile);
	SPEED_HIGH = JsonReader.readFloat("speed_high");
	SPEED_LOW = JsonReader.readFloat("speed_low");
	_ASSERTE(SPEED_HIGH > 0 && SPEED_LOW > 0);

	m_pPlayer = new CSprite;
	this->addChild(m_pPlayer, -1);

	m_pPlayerBg1 = JsonReader.readSprite("effect_sprite_1");
	m_pPlayerBg1->setAnchor(m_pPlayerBg1->getSize() / 2);
	this->addChild(m_pPlayerBg1, 0);
	m_pPlayerBg2 = JsonReader.readSprite("effect_sprite_2");
	m_pPlayerBg2->setAnchor(m_pPlayerBg2->getSize() / 2);
	this->addChild(m_pPlayerBg2, 0);

	m_PlayerAnm1 = JsonReader.readAnimation("player_anm_1");
	m_PlayerAnm2 = JsonReader.readAnimation("player_anm_2");

	m_SoundHandleGraze = DxLib::LoadSoundMem(LOCATE_FILE("se_graze.wav"));
	ChangeVolumeSoundMem(255 * 6 / 10, m_SoundHandleGraze);
	m_SoundHandleDead = DxLib::LoadSoundMem(LOCATE_FILE("se_pldead_00.wav"));
	m_SoundHandleShoot = DxLib::LoadSoundMem(LOCATE_FILE("se_plst_00.wav"));
	ChangeVolumeSoundMem(255 * 6 / 10, m_SoundHandleShoot);
	_ASSERTE(m_SoundHandleGraze != -1 && m_SoundHandleDead != -1 && m_SoundHandleShoot != -1);
}

//*********************************************************************
//FUNCTION:
void CPlayer::__destroy()
{
	CHECK_RESULT(DxLib::DeleteSoundMem(m_SoundHandleGraze));
	CHECK_RESULT(DxLib::DeleteSoundMem(m_SoundHandleDead));
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

	if (m_IsGrazed) m_State |= PLAYER_STATE_GRAZE;
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
}

//*********************************************************************
//FUNCTION:
void CPlayer::__updateAnimation()
{
	if ((m_State & PLAYER_STATE_MOVE_LEFT) || (m_State & PLAYER_STATE_MOVE_RIGHT))
	{
		m_pPlayer->setImageFile(m_PlayerAnm2.ImageFile, m_PlayerAnm2.forward());
		m_PlayerAnm1.reset();
	}
	else
	{
		m_pPlayer->setImageFile(m_PlayerAnm1.ImageFile, m_PlayerAnm1.forward());
		m_PlayerAnm2.reset();
	}

	m_pPlayer->setAnchor(m_pPlayer->getSize() / 2);
	m_pPlayer->setFlip(m_State & PLAYER_STATE_MOVE_RIGHT);

	m_pPlayerBg1->setRotation(m_pPlayerBg1->getRotation() + 0.02);
	m_pPlayerBg1->setVisible(m_State & PLAYER_STATE_LOW_SPEED);
	m_pPlayerBg2->setRotation(m_pPlayerBg2->getRotation() + 0.04);
}