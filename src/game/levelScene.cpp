#include "stdafx.h"
#include "engine/engine.h"
#include "engine/inputManager.h"
#include "engine/label.h"
#include "engine/sprite.h"
#include "engine/resourceManager.h"
#include "levelScene.h"
#include "titleScene.h"
#include "gameScene.h"

using namespace DxEngine;

namespace
{
	const int MENU_FONT_COLOE_NORMAL = 0x222222;
	const int MENU_FONT_EDGE_COLOE_NORMAL = 0x000000;
	const int MENU_FONT_COLOR_SELECTED = 0xffffff;
	const int MENU_FONT_EDGE_COLOR_SELECTED = 0xffee55;

	const std::vector<std::vector<std::string>> LEVEL_DESC =
	{
		{ "序章: 七色的人偶使",		"要说在祭典中出现在人们面前,表演着人偶技艺的魔法使的话,那就是爱丽丝·玛格特洛依德.\n她是一位能用魔法操控人偶,让它们表现得栩栩如生的技艺精湛的魔法使.\n\n金发与白皙的皮肤,她本人也有着人偶般的外表.\n她是属于由人类修行而成的魔法使,因此十分理解人类,在魔法使当中资质尚浅,属于新人.\n虽然已经不必要了,但仍然还保持着和人类一样的吃饭与睡觉的习惯.\n\n她平时住在魔法森林一座有好多人偶的小洋馆里.\n如果不小心在魔法森林迷路,走到了这里,则会被邀请住宿一晚.\n不过就算住下来,她也会继续研究人偶操控,不多说话,让人觉得很难受并想马上离开这里.\n但是,入夜的魔法森林是很可怕的,还是尽量忍耐一下吧." },
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
	CHECK_RESULT(DxLib::ChangeFont("simkai"));

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

	m_pImageLabel = new CImageLabel("alice_01.png");
	m_pImageLabel->setPosition(GRAPH_SIZE_X - m_pImageLabel->getSize().x, GRAPH_SIZE_Y - m_pImageLabel->getSize().y);
	m_pImageLabel->setColor(vec3i{ 200, 200, 200 });
	this->addChild(m_pImageLabel);

	m_pDescLabel = new CTextLabel("", 20, DX_FONTTYPE_NORMAL, GetColor(228, 231, 152), 0, 10);
	m_pDescLabel->setPosition(800, 200);
	this->addChild(m_pDescLabel);

	m_pDoll = new CSprite("shanghai.png");
	m_pDoll->setPosition(-50, 0);
	m_pDoll->setScale(0.6, 0.6);
	m_pDoll->setColor(vec3i{ 150, 150, 150 });
	this->addChild(m_pDoll);

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__updateDollPosition(vDeltaTime);
	__updateSelectedLabel();

	m_pDescLabel->setText(LEVEL_DESC[m_SelectedLabelIndex][1]);

	if (CHECK_HIT_KEY(KEY_INPUT_Z) || CHECK_HIT_KEY(KEY_INPUT_RETURN))
	{
		CEngine::getInstance()->setActiveScene(new CGameScene);
		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_ok_01.mp3"), DX_PLAYTYPE_BACK));
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
	int TopY = 128;
	CHECK_RESULT(DxLib::SetDrawBright(255, 255, 255));
	CHECK_RESULT(DxLib::DrawBox(GRAPH_SIZE_X*0.382, TopY, GRAPH_SIZE_X*0.382 + 6, GRAPH_SIZE_Y - 50, 0xffee55, FALSE));
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

//***********************************************************************************************
//FUNCTION:
void CLevelScene::__updateDollPosition(double vDeltaTime)
{
	int MinX = -100 - m_pDoll->getSize().x;
	int MaxX = GRAPH_SIZE_X + 100;

	int PosX = m_pDoll->getPosition().x;
	if (PosX > MaxX || PosX < MinX) { m_DollSpeed *= -1; m_pDoll->flip(); }

	m_pDoll->setPosition(PosX + m_DollSpeed * vDeltaTime, m_pDoll->getPosition().y);
}