#pragma once
#include <vector>
#include "engine/luaGlue.h"
#include "engine/scene.h"
#include "engine/sprite.h"
#include "engine/label.h"

using namespace DxEngine;

class CGameScene : public CScene
{
public:
	CGameScene(const char* vScriptFile);
	~CGameScene() = default;

	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

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

	lua_State* m_pLuaState = nullptr;
	std::string m_ScriptSource = "";
	std::vector<std::string> m_ScriptActions;
	unsigned m_ActionIndex = 0;

	CSprite* m_pLCharacter = nullptr;
	CSprite* m_pRCharacter = nullptr;
	CSprite* m_pBackground = nullptr;

	CTextLabel* m_pDialogueLabel = nullptr;
	CSprite*	m_pDialogBackground = nullptr;

	std::pair<CTextLabel*, CTextLabel*> m_HiScoreLabel;
	std::pair<CTextLabel*, CTextLabel*> m_ScoreLabel;
	std::pair<CTextLabel*, CTextLabel*> m_PlayerNumLabel;
	std::pair<CTextLabel*, CTextLabel*> m_BombNumLabel;
	std::pair<CTextLabel*, CTextLabel*> m_PowerLabel;
	std::pair<CTextLabel*, CTextLabel*> m_GrazeLabel;

	int m_Counter = 0;
};