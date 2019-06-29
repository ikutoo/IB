#include "stdafx.h"
#include "engine/engine.h"
#include "engine/inputManager.h"
#include "levelScene.h"
#include "titleScene.h"
#include "gameScene.h"

using namespace DxEngine;

namespace
{
	const int MENU_FONT_COLOE_NORMAL = 0x222222;
	const int MENU_FONT_COLOR_SELECTED = 0xffffff;

	const std::vector<std::vector<std::string>> LEVEL_DESC =
	{
		{ "序章: 玩弄人偶的少女",		"" },
		{ "第一章: 人偶失踪事件",		"" },
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

	for (int i = 0; i < 7; ++i)
	{
		auto pLabel = new CTextLabel(LEVEL_DESC[i][0], 32, DX_FONTTYPE_ANTIALIASING_4X4, MENU_FONT_COLOE_NORMAL);
		pLabel->setPosition(200, 150 + i * 100);

		m_MenuLabels.emplace_back(pLabel);
		this->addChild(pLabel);
	}

	m_pFlagLabel = new CImageLabel(LOCATE_IMAGE("flag.png"));
	m_pFlagLabel->setPosition(100, m_MenuLabels[0]->getPosition().y - 10);
	this->addChild(m_pFlagLabel);

	m_pImageLabel = new CImageLabel(LOCATE_IMAGE("alice.png"));
	m_pImageLabel->setSize(450, 600);
	m_pImageLabel->setPosition(WIDTH - m_pImageLabel->getSize().x, HEIGHT - m_pImageLabel->getSize().y);
	this->addChild(m_pImageLabel);

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__updateSelectedLabel();

	if (CHECK_HIT_KEY(KEY_INPUT_Z) || CHECK_HIT_KEY(KEY_INPUT_RETURN))
	{
		CEngine::getInstance()->setActiveScene(new CGameScene);
		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_SOUND("se_ok_01.mp3"), DX_PLAYTYPE_BACK));
	}
	else if (CHECK_HIT_KEY(KEY_INPUT_X))
	{
		CEngine::getInstance()->setActiveScene(new CTitleScene);
	}
}

//*********************************************************************
//FUNCTION:
void CLevelScene::drawV()
{
	CScene::drawV();
	CHECK_RESULT(DxLib::DrawLine(100, 100, WIDTH - 100, 100, 0x666666, 10));
	CHECK_RESULT(DxLib::DrawLine(WIDTH*0.382, 100, WIDTH*0.382, HEIGHT, 0x666666, 6));
}

//*********************************************************************
//FUNCTION:
void CLevelScene::destroyV()
{
	CScene::destroyV();
}

//*********************************************************************
//FUNCTION:
void CLevelScene::__updateSelectedLabel()
{
	bool IndexChanged = false;
	if (CHECK_HIT_KEY(KEY_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (CHECK_HIT_KEY(KEY_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_SOUND("se_select_01.mp3"), DX_PLAYTYPE_BACK));

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		if (i == m_SelectedLabelIndex)
			m_MenuLabels[i]->setFontColor(MENU_FONT_COLOR_SELECTED);
		else
			m_MenuLabels[i]->setFontColor(MENU_FONT_COLOE_NORMAL);
	}

	m_pFlagLabel->setPosition(m_pFlagLabel->getPosition().x, m_MenuLabels[m_SelectedLabelIndex]->getPosition().y - 10);
}