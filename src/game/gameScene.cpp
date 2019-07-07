#include "stdafx.h"
#include "engine/graphics2d.h"
#include "engine/utility.h"
#include "engine/inputManager.h"
#include "gameScene.h"
#include "barrageManager.h"
#include "barragePattern.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
CGameScene::CGameScene(const char* vScriptFile)
{
	_ASSERTE(vScriptFile);
	__setScriptSource(vScriptFile);
}

//*********************************************************************
//FUNCTION:
bool CGameScene::initV()
{
	if (!CScene::initV()) return false;

	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));

	CBarrageManager::getInstance()->init(this);

	__initLuaEnv();
	__initUI();

	__performLuaScript(m_ScriptActions[m_ActionIndex++].c_str());

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__updateBarrage();

	m_pLParticles->update();
	m_pRParticles->update();

	if (CHECK_HIT_KEY(KEY_INPUT_Z))
	{
		if (m_ActionIndex < m_ScriptActions.size())
			__performLuaScript(m_ScriptActions[m_ActionIndex++].c_str());
	}

	m_Counter++;
}

//*********************************************************************
//FUNCTION:
void CGameScene::destroyV()
{
	__closeLuaEvn();
	CBarrageManager::getInstance()->destroy();
	CScene::destroyV();
}

//*********************************************************************
//FUNCTION:
bool CGameScene::__initUI()
{
	m_pBackground = new CSprite;
	m_pBackground->setBrightness({ 50, 50, 50 });
	this->addChild(m_pBackground, 1);

	m_pLParticles = new CParticle01(recti{ 0, 0, 480, GRAPH_SIZE_Y }, 2.0);
	this->addChild(m_pLParticles, 1);

	m_pRParticles = new CParticle01(recti{ GRAPH_SIZE_X - 500, 0, 500, GRAPH_SIZE_Y }, 2.0);
	this->addChild(m_pRParticles, 1);

	m_pLCharacter = new CSprite;
	m_pLCharacter->setPosition(-50, 250);
	m_pLCharacter->setScale(0.9, 0.9);
	this->addChild(m_pLCharacter, 1);

	m_pRCharacter = new CSprite;
	m_pRCharacter->setPosition(1300, 350);
	m_pRCharacter->flip();
	this->addChild(m_pRCharacter, 1);

	m_pDialogBackground = new CSprite;
	m_pDialogBackground->setPosition(500, 800);
	this->addChild(m_pDialogBackground, 1);

	const int FontSizeL = 35, FontSizeM = 25;
	float PosX = 1450;
	m_HiScoreLabel.first = new CTextLabel("HI-SCORE", FontSizeL, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_HiScoreLabel.first->setPosition(PosX, 20);
	this->addChild(m_HiScoreLabel.first, 1);

	m_ScoreLabel.first = new CTextLabel("SCORE", FontSizeL, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_ScoreLabel.first->setPosition(PosX, 70);
	this->addChild(m_ScoreLabel.first, 1);

	m_PlayerNumLabel.first = new CTextLabel("Player", FontSizeM, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_PlayerNumLabel.first->setPosition(PosX, 150);
	this->addChild(m_PlayerNumLabel.first, 1);

	m_BombNumLabel.first = new CTextLabel("Bomb", FontSizeM, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_BombNumLabel.first->setPosition(PosX, 200);
	this->addChild(m_BombNumLabel.first, 1);

	m_PowerLabel.first = new CTextLabel("Power", FontSizeM, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_PowerLabel.first->setPosition(PosX, 270);
	this->addChild(m_PowerLabel.first, 1);

	m_GrazeLabel.first = new CTextLabel("Graze", FontSizeM, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_GrazeLabel.first->setPosition(PosX, 320);
	this->addChild(m_GrazeLabel.first, 1);

	float OffsetX = 300;
	m_HiScoreLabel.second = new CTextLabel("000000", FontSizeL, DX_FONTTYPE_ANTIALIASING);
	m_HiScoreLabel.second->setPosition(PosX + OffsetX, m_HiScoreLabel.first->getPosition().y);
	this->addChild(m_HiScoreLabel.second, 1);

	m_ScoreLabel.second = new CTextLabel("000000", FontSizeL, DX_FONTTYPE_ANTIALIASING);
	m_ScoreLabel.second->setPosition(PosX + OffsetX, m_ScoreLabel.first->getPosition().y);
	this->addChild(m_ScoreLabel.second, 1);

	m_PlayerNumLabel.second = new CTextLabel("000", FontSizeM, DX_FONTTYPE_ANTIALIASING);
	m_PlayerNumLabel.second->setPosition(PosX + OffsetX, m_PlayerNumLabel.first->getPosition().y);
	this->addChild(m_PlayerNumLabel.second, 1);

	m_BombNumLabel.second = new CTextLabel("000", FontSizeM, DX_FONTTYPE_ANTIALIASING);
	m_BombNumLabel.second->setPosition(PosX + OffsetX, m_BombNumLabel.first->getPosition().y);
	this->addChild(m_BombNumLabel.second, 1);

	m_PowerLabel.second = new CTextLabel("000", FontSizeM, DX_FONTTYPE_ANTIALIASING);
	m_PowerLabel.second->setPosition(PosX + OffsetX, m_PowerLabel.first->getPosition().y);
	this->addChild(m_PowerLabel.second, 1);

	m_GrazeLabel.second = new CTextLabel("000", FontSizeM, DX_FONTTYPE_ANTIALIASING);
	m_GrazeLabel.second->setPosition(PosX + OffsetX, m_GrazeLabel.first->getPosition().y);
	this->addChild(m_GrazeLabel.second, 1);

	m_pChNameLabel = new CTextLabel("", 26);
	m_pChNameLabel->setFontColor(0xffff00);
	m_pChNameLabel->setPosition(540, 812);
	this->addChild(m_pChNameLabel, 1);

	m_pDialogueLabel = new CTextLabel("", 22);
	m_pDialogueLabel->setFontColor(GetColor(228, 231, 152));
	m_pDialogueLabel->setPosition(565, 880);
	this->addChild(m_pDialogueLabel, 1);

	return true;
}

//*********************************************************************
//FUNCTION:
void CGameScene::__updateBarrage()
{
	if (m_Counter == 100)
	{
		CBarrage* pBarrage = new CBarrage(CBarragePattern::barragePattern001);
		pBarrage->setPosition(GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2);
		pBarrage->setLiveTime(3000);
		CBarrageManager::getInstance()->startBarrage(pBarrage);
	}
}

//*********************************************************************
//FUNCTION:
void CGameScene::__initLuaEnv()
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);
	__registerLuaGlue();
}

//*********************************************************************
//FUNCTION:
void CGameScene::__closeLuaEvn()
{
	lua_close(m_pLuaState);
}

//*********************************************************************
//FUNCTION:
void CGameScene::__setScriptSource(const char* vFilePath)
{
	m_ScriptSource = Utility::readFileToString(vFilePath);
	m_ScriptActions = Utility::splitString(m_ScriptSource, "#ACTION");
	m_ActionIndex = 0;
}

//*********************************************************************
//FUNCTION:
void CGameScene::__registerLuaGlue()
{
	lua_register(m_pLuaState, "log", luaGlue::log);
	lua_register(m_pLuaState, "playMusic", luaGlue::playMusic);
	lua_register(m_pLuaState, "setNodePosition", luaGlue::setNodePosition);
	lua_register(m_pLuaState, "setNodeRotation", luaGlue::setNodeRotation);

	lua_registry_member_function(m_pLuaState, "setBackground", this, &CGameScene::__setBackgroundImage);
	lua_registry_member_function(m_pLuaState, "setLCharacter", this, &CGameScene::__setLCharaterImage);
	lua_registry_member_function(m_pLuaState, "setRCharacter", this, &CGameScene::__setRCharaterImage);
	lua_registry_member_function(m_pLuaState, "setDialogue", this, &CGameScene::__setDialogue);
	lua_registry_member_function(m_pLuaState, "setCharacterName", this, &CGameScene::__setCharacterName);
	lua_registry_member_function(m_pLuaState, "beginDialogue", this, &CGameScene::__beginDialogue);
	lua_registry_member_function(m_pLuaState, "endDialogue", this, &CGameScene::__endDialogue);
}

//*********************************************************************
//FUNCTION:
void CGameScene::__performLuaScript(const char* vScript)
{
	int Ret = luaL_dostring(m_pLuaState, vScript);
	_ASSERTE(0 == Ret);
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setBackgroundImage(lua_State* vioLuaState)
{
	auto FilePath = lua_tostring(vioLuaState, 1);
	m_pBackground->setImageFile(FilePath);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setLCharaterImage(lua_State* vioLuaState)
{
	auto FilePath = lua_tostring(vioLuaState, 1);
	m_pLCharacter->setImageFile(FilePath);
	return 0;
}

//***********************************************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setRCharaterImage(lua_State* vioLuaState)
{
	auto FilePath = lua_tostring(vioLuaState, 1);
	m_pRCharacter->setImageFile(FilePath);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__beginDialogue(lua_State* vioLuaState)
{
	m_GameState = EGameState::IN_DIALOGUE;
	m_pDialogBackground->setImageFile("dialogue.png");
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__endDialogue(lua_State* vioLuaState)
{
	m_GameState = EGameState::NORMAL;
	m_pDialogBackground->setImageFile("");
	m_pLCharacter->setImageFile("");
	m_pDialogueLabel->setText("");
	m_pChNameLabel->setText("");
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setDialogue(lua_State* vioLuaState)
{
	auto Text = lua_tostring(vioLuaState, 1);
	m_pDialogueLabel->setText(Text);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setCharacterName(lua_State* vioLuaState)
{
	auto Text = lua_tostring(vioLuaState, 1);
	m_pChNameLabel->setText(Text);
	return 0;
}