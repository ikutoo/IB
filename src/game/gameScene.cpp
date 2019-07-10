#include "stdafx.h"
#include "gameScene.h"
#include <iostream>
#include "engine/graphics2d.h"
#include "engine/utility.h"
#include "engine/inputManager.h"
#include "engine/jsonUtil.h"
#include "engine/engine.h"
#include "engine/renderTarget.h"
#include "barrageManager.h"
#include "barragePattern.h"
#include "player.h"

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
bool CGameScene::_initV()
{
	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));

	__initLuaEnv();
	__initUI();

	m_pPlayer = new CPlayer("player_00a.cfg");
	m_pPlayer->setPosition(960, 900);
	this->addChild(m_pPlayer);

	__performLuaScript(m_ScriptActions[m_ActionIndex++].c_str());

	m_pBarrageRenderTarget = new CRenderTarget(GRAPH_SIZE_X, GRAPH_SIZE_Y);
	this->addChild(m_pBarrageRenderTarget, 0.5);

	m_pBarrageContainer = new CSprite;
	m_pBarrageContainer->setRenderGraph(m_pBarrageRenderTarget->getRenderGraph());
	this->addChild(m_pBarrageContainer);

	CBarrageManager::getInstance()->init(m_pBarrageContainer);

	m_BarrageSoftImage = MakeARGB8ColorSoftImage(1, 1);

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::_updateV(double vDeltaTime)
{
	__updateBarrage();
	__detectCollision();

	m_pLParticles->updateV();
	m_pRParticles->updateV();

	if (CHECK_HIT_KEY(KEY_INPUT_Z))
	{
		if (m_ActionIndex < m_ScriptActions.size())
			__performLuaScript(m_ScriptActions[m_ActionIndex++].c_str());
	}

	if (CHECK_HIT_KEY(KEY_INPUT_ESCAPE)) CEngine::getInstance()->stop();

	m_Counter++;
}

//*********************************************************************
//FUNCTION:
void CGameScene::_destroyV()
{
	CHECK_RESULT(DxLib::DeleteSoftImage(m_BarrageSoftImage));

	__closeLuaEvn();
	CBarrageManager::getInstance()->destroy();
}

//*********************************************************************
//FUNCTION:
bool CGameScene::__initUI()
{
	CJsonReader JsonReader("game_scene.ui");
	m_pUIRootNode = JsonReader.getRootNode();
	this->addChild(m_pUIRootNode, 1);

	m_pLParticles = new CParticle01(recti{ 0, 0, 480, GRAPH_SIZE_Y }, 2.0);
	m_pUIRootNode->addChild(m_pLParticles);

	m_pRParticles = new CParticle01(recti{ GRAPH_SIZE_X - 500, 0, 500, GRAPH_SIZE_Y }, 2.0);
	m_pUIRootNode->addChild(m_pRParticles);

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
void CGameScene::__detectCollision()
{
	CHECK_RESULT(DxLib::SetDrawScreen(m_pBarrageRenderTarget->getRenderGraph()));

	GetDrawScreenSoftImage(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, m_pPlayer->getPosition().x + 1, m_pPlayer->getPosition().y + 1, m_BarrageSoftImage);

	int r, g, b, a;
	GetPixelSoftImage(m_BarrageSoftImage, 0, 0, &r, &g, &b, &a);

	const int COLLISION_ALPHA_THRESHOLD = 20;
	static int i = 0;
	if (a > COLLISION_ALPHA_THRESHOLD)
	{
		std::cout << "collision: " << i++ << std::endl;
	}

	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));
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
	__findUISprite("bgSprite")->setImageFile(FilePath);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setLCharaterImage(lua_State* vioLuaState)
{
	auto FilePath = lua_tostring(vioLuaState, 1);
	__findUISprite("lChSprite")->setImageFile(FilePath);
	return 0;
}

//***********************************************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setRCharaterImage(lua_State* vioLuaState)
{
	auto FilePath = lua_tostring(vioLuaState, 1);
	__findUISprite("rChSprite")->setImageFile(FilePath);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__beginDialogue(lua_State* vioLuaState)
{
	m_GameState = EGameState::IN_DIALOGUE;
	__findUISprite("dialogueBgSprite")->setImageFile("ui.png", recti{ 1024, 256, 920, 184 });
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__endDialogue(lua_State* vioLuaState)
{
	m_GameState = EGameState::NORMAL;
	__findUISprite("dialogueBgSprite")->setImageFile("");
	__findUISprite("lChSprite")->setImageFile("");
	__findUILabel("dialogueLabel")->setText("");
	__findUILabel("chNameLabel")->setText("");
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setDialogue(lua_State* vioLuaState)
{
	auto Text = lua_tostring(vioLuaState, 1);
	__findUILabel("dialogueLabel")->setText(Text);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__setCharacterName(lua_State* vioLuaState)
{
	auto Text = lua_tostring(vioLuaState, 1);
	__findUILabel("chNameLabel")->setText(Text);
	return 0;
}

//***********************************************************************************************
//FUNCTION:
CSprite* CGameScene::__findUISprite(const std::string& vName)
{
	_ASSERTE(m_pUIRootNode);
	auto pSprite = dynamic_cast<CSprite*>(m_pUIRootNode->findChild(vName));
	_ASSERTE(pSprite);
	return pSprite;
}

//***********************************************************************************************
//FUNCTION:
CLabel* CGameScene::__findUILabel(const std::string& vName)
{
	_ASSERTE(m_pUIRootNode);
	auto pLabel = dynamic_cast<CLabel*>(m_pUIRootNode->findChild(vName));
	_ASSERTE(pLabel);
	return pLabel;
}