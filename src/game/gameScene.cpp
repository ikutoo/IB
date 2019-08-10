#include "stdafx.h"
#include "gameScene.h"
#include <iostream>
#include "engine/graphics.h"
#include "engine/utility.h"
#include "engine/inputManager.h"
#include "engine/resourceManager.h"
#include "engine/jsonUtil.h"
#include "engine/engine.h"
#include "engine/renderTarget.h"
#include "engine/action.h"
#include "engine/actionManager.h"
#include "barrageManager.h"
#include "barragePattern.h"
#include "playerAlice.h"
#include "collision.h"
#include "background3d.h"
#include "enemy.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
CGameScene::CGameScene(const char* vScriptFile) : m_ScriptFile(vScriptFile)
{
	_ASSERTE(vScriptFile);
}

//*********************************************************************
//FUNCTION:
bool CGameScene::_initV()
{
	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));

	__initLuaEnv();
	__initUI();

	m_pPlayer = new CPlayerAlice("player_00a.cfg");
	this->addChild(m_pPlayer);

	m_pBarrageRenderTarget = new CRenderTarget(GRAPH_SIZE_X, GRAPH_SIZE_Y);
	this->addChild(m_pBarrageRenderTarget, 0.5);

	m_pPlayerBarrageContainer = new CSprite;
	this->addChild(m_pPlayerBarrageContainer, -1.0);
	m_pEnemyBarrageContainer = new CSprite;
	m_pEnemyBarrageContainer->setRenderGraph(m_pBarrageRenderTarget->getRenderGraph());
	this->addChild(m_pEnemyBarrageContainer);

	m_pCollisionDetector = new CCollisionDetector;

	CBarrageManager::getInstance()->init(m_pEnemyBarrageContainer, m_pPlayerBarrageContainer);

	__performLuaFunc("init");

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::_updateV(double vDeltaTime)
{
	__updateBarrage();
	__detectCollision();
	__updateUI();

	m_pLParticles->updateV();
	m_pRParticles->updateV();

	if (m_GameState == EGameState::IN_DIALOGUE)
	{
		if (m_ActionIndex < m_DialogueActions.size() && checkHit(GAME_INPUT_Z))
			__performLuaSource(m_DialogueActions[m_ActionIndex++].c_str());
		else if (m_ActionIndex >= m_DialogueActions.size())
			__endDialogue(nullptr);
	}

	if (checkHit(GAME_INPUT_ESCAPE)) CEngine::getInstance()->stop();

	if (m_GameState == EGameState::NORMAL)
	{
		__performLuaFunc("update");
		m_Counter++;
	}
}

//*********************************************************************
//FUNCTION:
void CGameScene::_destroyV()
{
	SAFE_DELETE(m_pCollisionDetector);
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
	CBarrageManager::getInstance()->setPlayerPosition(m_pPlayer->getPosition());

	//if (m_Counter == 100)
	//{
	//	CBarrage* pBarrage = new CBarrage(CBarragePattern::enemyBarrage000);
	//	pBarrage->setPosition(GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2);
	//	pBarrage->setLiveTime(3000);
	//	CBarrageManager::getInstance()->startBarrage(pBarrage);
	//}
}

//*********************************************************************
//FUNCTION:
void CGameScene::__updateUI()
{
	//auto pGrazeLabel = dynamic_cast<CLabel*>(m_pUIRootNode->findChild("grazeLabel"));
	//pGrazeLabel->setText(std::to_string(m_pPlayer->getGrazeScore()));
}

//*********************************************************************
//FUNCTION:
void CGameScene::__detectCollision()
{
	m_pCollisionDetector->detectCollision(m_pPlayer->getPosition(), m_pBarrageRenderTarget->getRenderGraph());
	if (m_pCollisionDetector->isPlayerHit()) m_pPlayer->dead();
	else m_pPlayer->graze(m_pCollisionDetector->isPlayerGrazed());
}

//*********************************************************************
//FUNCTION:
void CGameScene::__initLuaEnv()
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);
	__registerLuaGlue();

	auto Ret = luaL_loadfile(m_pLuaState, m_ScriptFile.c_str());
	_ASSERTE(0 == Ret);

	lua_pcall(m_pLuaState, 0, 0, 0);
}

//*********************************************************************
//FUNCTION:
void CGameScene::__closeLuaEvn()
{
	lua_close(m_pLuaState);
}

//*********************************************************************
//FUNCTION:
void CGameScene::__setDialogueScript(const char* vFilePath)
{
	m_DialogueSource = Utility::readFileToString(CResourceManager::getInstance()->locateFile(vFilePath));
	m_DialogueActions = Utility::splitString(m_DialogueSource, "#ACTION");
	m_ActionIndex = 0;
}

//*********************************************************************
//FUNCTION:
void CGameScene::__performLuaFunc(const char* vFuncName)
{
	lua_getglobal(m_pLuaState, vFuncName);

	auto Ret = lua_pcall(m_pLuaState, 0, 0, 0);
	_ASSERTE(Ret == 0);
}

//*********************************************************************
//FUNCTION:
void CGameScene::__performLuaSource(const char* vSource)
{
	int Ret = luaL_dostring(m_pLuaState, vSource);
	_ASSERTE(0 == Ret);
}

//*********************************************************************
//FUNCTION:
void CGameScene::__registerLuaGlue()
{
	lua_register(m_pLuaState, "log", luaGlue::log);
	lua_register(m_pLuaState, "playMusic", luaGlue::playMusic);
	lua_register(m_pLuaState, "setPosition", luaGlue::setNodePosition);
	lua_register(m_pLuaState, "setRotation", luaGlue::setNodeRotation);

	lua_registry_member_function(m_pLuaState, "setBackground", this, &CGameScene::__setBackgroundImage);
	lua_registry_member_function(m_pLuaState, "setLCharacter", this, &CGameScene::__setLCharaterImage);
	lua_registry_member_function(m_pLuaState, "setRCharacter", this, &CGameScene::__setRCharaterImage);
	lua_registry_member_function(m_pLuaState, "setDialogue", this, &CGameScene::__setDialogue);
	lua_registry_member_function(m_pLuaState, "setCharacterName", this, &CGameScene::__setCharacterName);
	lua_registry_member_function(m_pLuaState, "beginDialogue", this, &CGameScene::__beginDialogue);
	lua_registry_member_function(m_pLuaState, "endDialogue", this, &CGameScene::__endDialogue);
	lua_registry_member_function(m_pLuaState, "startBgAnm", this, &CGameScene::__startBgAnimation);
	lua_registry_member_function(m_pLuaState, "getCounter", this, &CGameScene::__getCounter);
	lua_registry_member_function(m_pLuaState, "displayStageInfo", this, &CGameScene::__displayStageInfo);
	lua_registry_member_function(m_pLuaState, "createEnemy", this, &CGameScene::__createEnemy);
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

	auto FilePath = lua_tostring(vioLuaState, 1);
	__setDialogueScript(FilePath);

	if (m_DialogueActions.size() > 0)
		__performLuaSource(m_DialogueActions[m_ActionIndex++].c_str());

	m_pPlayer->pause();

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

	WaitTimer(200);
	m_pPlayer->resume();

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

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__startBgAnimation(lua_State *vioLuaState)
{
	auto pStageBg = new CBackground3d;
	this->addChild(pStageBg, -2.0);
	return 0;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__getCounter(lua_State *vioLuaState)
{
	lua_pushnumber(m_pLuaState, m_Counter);
	return 1;
}

//*********************************************************************
//FUNCTION:
LUAGLUE CGameScene::__displayStageInfo(lua_State *vioLuaState)
{
	//stage title
	{
		auto pSprite = new CSprite("ui.png", recti{ 1070, 458, 366, 104 });
		pSprite->setAnchor(pSprite->getSize() / 2);
		this->addChild(pSprite);

		std::vector<CAction*> Sequnce;
		float cx = GRAPH_SIZE_X / 2, cy = GRAPH_SIZE_Y * 0.4;
		Sequnce.emplace_back(new CMoveTo(pSprite, vec2f{ cx - 800, cy }, vec2f{ cx, cy }, 1000));
		Sequnce.emplace_back(new CMoveTo(pSprite, vec2f{ cx, cy }, vec2f{ cx + 800, cy }, 1000, 4000));

		auto pActionSequence = new CActionSequence(pSprite, Sequnce);
		pActionSequence->setDestroyTargetOnDoneHint();
		CActionManager::getInstance()->startAction(pActionSequence);
	}
	//bgm title
	{
		auto pSprite = new CSprite("ui.png", recti{ 1100, 585, 298, 33 });
		pSprite->setAnchor(pSprite->getSize() / 2);
		this->addChild(pSprite);

		std::vector<CAction*> Sequnce;
		float cx = GRAPH_SIZE_X / 2, cy = GRAPH_SIZE_Y * 0.4 + 80;
		Sequnce.emplace_back(new CMoveTo(pSprite, vec2f{ cx + 800, cy }, vec2f{ cx, cy }, 1000));
		Sequnce.emplace_back(new CMoveTo(pSprite, vec2f{ cx, cy }, vec2f{ cx - 800, cy }, 1000, 4000));

		auto pActionSequence = new CActionSequence(pSprite, Sequnce);
		pActionSequence->setDestroyTargetOnDoneHint();
		CActionManager::getInstance()->startAction(pActionSequence);
	}

	return 0;
}

//***********************************************************************************************
//FUNCTION:
LUAGLUE CGameScene::__createEnemy(lua_State* vioLuaState)
{
	int Index = 0;
	auto FilePath = lua_tostring(vioLuaState, ++Index);
	recti Rect;
	Rect.x = lua_tointeger(vioLuaState, ++Index);
	Rect.y = lua_tointeger(vioLuaState, ++Index);
	Rect.w = lua_tointeger(vioLuaState, ++Index);
	Rect.h = lua_tointeger(vioLuaState, ++Index);

	auto pEnemy = new CEnemy(FilePath, Rect);
	this->addChild(pEnemy);

	lua_pushlightuserdata(vioLuaState, pEnemy);

	return 1;
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