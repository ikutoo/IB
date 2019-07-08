#pragma once
#include <vector>
#include "engine/luaGlue.h"
#include "engine/scene.h"
#include "engine/sprite.h"
#include "engine/label.h"
#include "particles.h"

using namespace DxEngine;

enum class EGameState : char
{
	UNDEFINED = 0,
	NORMAL,
	PAUSED,
	IN_DIALOGUE
};

class CPlayer;

class CGameScene : public CScene
{
public:
	CGameScene(const char* vScriptFile);
	~CGameScene() = default;

	virtual bool _initV() override;
	virtual void _updateV(double vDeltaTime) override;
	virtual void _destroyV() override;

private:
	bool __initUI();
	void __updateBarrage();

	void __initLuaEnv();
	void __registerLuaGlue();
	void __performLuaScript(const char* vScript);
	void __closeLuaEvn();

	void __setScriptSource(const char* vFilePath);

	LUAGLUE __setBackgroundImage(lua_State* vioLuaState);
	LUAGLUE __setLCharaterImage(lua_State* vioLuaState);
	LUAGLUE __setRCharaterImage(lua_State* vioLuaState);
	LUAGLUE __beginDialogue(lua_State* vioLuaState);
	LUAGLUE __endDialogue(lua_State* vioLuaState);
	LUAGLUE __setDialogue(lua_State* vioLuaState);
	LUAGLUE __setCharacterName(lua_State* vioLuaState);

	EGameState m_GameState = EGameState::UNDEFINED;

	lua_State* m_pLuaState = nullptr;
	std::string m_ScriptSource = "";
	std::vector<std::string> m_ScriptActions;
	unsigned m_ActionIndex = 0;

	CPlayer* m_pPlayer = nullptr;

	CSprite* m_pLCharacter = nullptr;
	CSprite* m_pRCharacter = nullptr;
	CSprite* m_pBackground = nullptr;

	CLabel* m_pChNameLabel = nullptr;
	CLabel* m_pDialogueLabel = nullptr;
	CSprite*	m_pDialogBackground = nullptr;

	CParticle01* m_pLParticles = nullptr;
	CParticle01* m_pRParticles = nullptr;

	std::pair<CSprite*, CLabel*> m_HiScoreLabel;
	std::pair<CSprite*, CLabel*> m_ScoreLabel;
	std::pair<CSprite*, CLabel*> m_PlayerNumLabel;
	std::pair<CSprite*, CLabel*> m_BombNumLabel;
	std::pair<CSprite*, CLabel*> m_PowerLabel;
	std::pair<CSprite*, CLabel*> m_GrazeLabel;

	int m_Counter = 0;
};