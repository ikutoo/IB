#include "stdafx.h"
#include "engine/engine.h"
#include "engine/inputManager.h"
#include "engine/label.h"
#include "engine/sprite.h"
#include "engine/resourceManager.h"
#include "engine/graphics2d.h"
#include "levelScene.h"
#include "titleScene.h"
#include "gameScene.h"
#include "transparentWindow.h"
#include "common.h"

using namespace DxEngine;

namespace
{
	const int MENU_FONT_COLOE_NORMAL = 0x222222;
	const int MENU_FONT_EDGE_COLOE_NORMAL = 0x000000;
	const int MENU_FONT_COLOR_SELECTED = 0xffffff;
	const int MENU_FONT_EDGE_COLOR_SELECTED = 0xffee55;

	const std::vector<std::vector<std::string>> LEVEL_DESC =
	{
		{ "序章: 人偶失踪事件",		"  在魔法森林中心的一座小洋馆里,居住着一位热衷于人偶技艺的魔法使,她能用魔法操纵人偶,使其表现的栩栩如生.\n她本人也有着人偶般美丽的外表，" },
		{ "第一章: 七色的人偶使",		"" },
		{ "第二章: 魔法森林的访客",	"" },
		{ "第三章: 是她吗 ?",			"" },
		{ "第四章: 最终的抉择",		"" },
		{ "第五章: 无法抵达的彼岸",	"" },
		{ "终章: ? ? ?",				"" }
	};
}

//*********************************************************************
//FUNCTION:
bool CLevelScene::initV()
{
	if (!CScene::initV()) return false;

	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));
	CHECK_RESULT(DxLib::ChangeFont("simkai"));

	__initUI();

	m_pTransWindow = new CTransparentWindow;
	SetActiveWindow(DxLib::GetMainWindowHandle());

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	m_pTransWindow->update(vDeltaTime);

	__updateSelectedLabel();

	m_pDescLabel->setText(LEVEL_DESC[m_SelectedLabelIndex][1]);

	if (CHECK_HIT_KEY(KEY_INPUT_Z) || CHECK_HIT_KEY(KEY_INPUT_RETURN))
	{
		char ScriptFileName[0xff];
		sprintf(ScriptFileName, "%slevel%d.lua", RES_SCR_ROOT.c_str(), m_SelectedLabelIndex);
		CEngine::getInstance()->setActiveScene(new CGameScene(ScriptFileName));

		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_ok_01.mp3"), DX_PLAYTYPE_BACK));
	}
	else if (CHECK_HIT_KEY(KEY_INPUT_X))
	{
		CEngine::getInstance()->setActiveScene(new CTitleScene);
	}
}

//*********************************************************************
//FUNCTION:
void CLevelScene::destroyV()
{
	SAFE_DELETE(m_pTransWindow);
	SetActiveWindow(DxLib::GetMainWindowHandle());
	CScene::destroyV();
}

//*********************************************************************
//FUNCTION:
bool CLevelScene::__initUI()
{
	for (int i = 0; i < 7; ++i)
	{
		auto pLabel = new CTextLabel(LEVEL_DESC[i][0], 32, DX_FONTTYPE_ANTIALIASING_EDGE, MENU_FONT_COLOE_NORMAL, MENU_FONT_EDGE_COLOE_NORMAL);
		pLabel->setPosition(200, 200 + i * 100);

		m_MenuLabels.emplace_back(pLabel);
		this->addChild(pLabel);
	}

	m_pFlagLabel = new CImageLabel("flag.png");
	m_pFlagLabel->setPosition(100, m_MenuLabels[0]->getPosition().y - 10);
	this->addChild(m_pFlagLabel);

	m_pImageLabel = new CImageLabel("alice_00.png");
	m_pImageLabel->setPosition(GRAPH_SIZE_X - m_pImageLabel->getSize().x, GRAPH_SIZE_Y - m_pImageLabel->getSize().y);
	m_pImageLabel->setBrightness(vec3i{ 200, 200, 200 });
	this->addChild(m_pImageLabel);

	m_pDescLabel = new CTextLabel("", 20, DX_FONTTYPE_NORMAL, GetColor(228, 231, 152), 0, 10);
	m_pDescLabel->setPosition(800, 200);
	this->addChild(m_pDescLabel);

	int TopY = 128;
	auto pBox = new CBox2D(recti{ (int)(GRAPH_SIZE_X*0.382), TopY, 6, GRAPH_SIZE_Y - TopY - 50 }, 0xffee55, false);
	this->addChild(pBox);

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::__updateSelectedLabel()
{
	bool IndexChanged = false;
	if (CHECK_HIT_KEY(KEY_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (CHECK_HIT_KEY(KEY_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_select_01.mp3"), DX_PLAYTYPE_BACK));

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		if (i == m_SelectedLabelIndex)
		{
			m_MenuLabels[i]->setFontColor(MENU_FONT_COLOR_SELECTED);
			m_MenuLabels[i]->setEdgeColor(MENU_FONT_EDGE_COLOR_SELECTED);
		}
		else
		{
			m_MenuLabels[i]->setFontColor(MENU_FONT_COLOE_NORMAL);
			m_MenuLabels[i]->setEdgeColor(MENU_FONT_EDGE_COLOE_NORMAL);
		}
	}

	m_pFlagLabel->setPosition(m_pFlagLabel->getPosition().x, m_MenuLabels[m_SelectedLabelIndex]->getPosition().y - 10);
}