#include "stdafx.h"
#include "engine/engine.h"
#include "engine/inputManager.h"
#include "engine/label.h"
#include "engine/sprite.h"
#include "engine/resourceManager.h"
#include "engine/graphics.h"
#include "levelScene.h"
#include "gameScene.h"
#include "transparentWindow.h"
#include "common.h"

using namespace DxEngine;

namespace
{
	const int MENU_FONT_COLOE_NORMAL = 0x222222;
	const int MENU_FONT_EDGE_COLOE_NORMAL = 0x000000;
	const int MENU_FONT_COLOR_SELECTED = 0xffffff;
	const int MENU_FONT_EDGE_COLOR_SELECTED = GetColor(135, 135, 247);

	const std::vector<std::vector<std::string>> LEVEL_DESC =
	{
		{ "����: ��Ū��ż����Ů",		"    ��ħ��ɭ�����ĵ�һ��С�����,��ס��һλ��������ż���յ�ħ��ʹ,������ħ��\n������ż,ʹ����ֵ���������.\n\n    ������Ҳ������ż�����������,��ɫ�Ķ̷������Ƥ��,ʱ������һ���������\n����ɫ��ȹ.\n\n    ��ƽʱϲ���������ռ�������ż,����ż������Ҫ����������,���ڶ���ż��һ��\n����ƽ�������Ҹ�������.\n\n    ����,���Ǻ�ƽ��һ����..." },
		{ "��һ��: �������ε�ʧ��",		"" },
		{ "�ڶ���: ħ��ɭ�ֵķÿ�",	"" },
		{ "������: ������ ?",			"" },
		{ "������: ���յľ���",		"" },
		{ "������: �޷��ִ�ı˰�",	"" },
		{ "����: ? ? ?",				"" }
	};
}

//*********************************************************************
//FUNCTION:
bool CLevelScene::_initV()
{
	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));
	CHECK_RESULT(DxLib::ChangeFont("simkai"));

	__initUI();

	if (!CEngine::getInstance()->isFullScreen()) m_pTransWindow = new CTransparentWindow;

	SetActiveWindow(DxLib::GetMainWindowHandle());

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::_updateV(double vDeltaTime)
{
	if (!CEngine::getInstance()->isFullScreen()) m_pTransWindow->update(vDeltaTime);

	__updateSelectedLabel();

	m_pDescLabel->setText(LEVEL_DESC[m_SelectedLabelIndex][1]);

	for (auto pMagicCircle : m_MagicCircles) pMagicCircle->setAngle(pMagicCircle->getAngle() + 0.002);

	if (checkHit(GAME_INPUT_ENTER) || checkHit(GAME_INPUT_Z))
	{
		char ScriptFileName[0xff];
		sprintf(ScriptFileName, "%sstage%d.lua", DATA_PATH.c_str(), m_SelectedLabelIndex);
		CEngine::getInstance()->setActiveScene(new CGameScene(ScriptFileName));

		//CHECK_RESULT(DxLib::StopMusic());
		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_ok_00.wav"), DX_PLAYTYPE_BACK));
	}
	else if (checkHit(GAME_INPUT_ESCAPE) || checkHit(GAME_INPUT_X))
	{
		auto pScene = CEngine::getInstance()->popScene();
		CEngine::getInstance()->setActiveScene(pScene);
		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_cancel_00.wav"), DX_PLAYTYPE_BACK));
	}
}

//*********************************************************************
//FUNCTION:
void CLevelScene::_destroyV()
{
	SAFE_DELETE(m_pTransWindow);
	SetActiveWindow(DxLib::GetMainWindowHandle());
}

//*********************************************************************
//FUNCTION:
bool CLevelScene::__initUI()
{
	for (int i = 0; i < 7; ++i)
	{
		auto pLabel = new CLabel(LEVEL_DESC[i][0], 32, DX_FONTTYPE_ANTIALIASING_EDGE, MENU_FONT_COLOE_NORMAL, MENU_FONT_EDGE_COLOE_NORMAL);
		pLabel->setPosition(200, 200 + i * 100);

		m_MenuLabels.emplace_back(pLabel);
		this->addChild(pLabel);
	}

	m_pFlagSprite = new CSprite("ui.png", recti{ 64, 640, 74, 54 });
	m_pFlagSprite->setPosition(100, m_MenuLabels[0]->getPosition().y - 10);
	m_pFlagSprite->setBrightness({ 135, 135, 247 });
	this->addChild(m_pFlagSprite);

	m_pChImage = new CSprite("ui.png", recti{ 256, 256, 480, 480 });
	m_pChImage->setPosition(GRAPH_SIZE_X - m_pChImage->getSize().x, GRAPH_SIZE_Y - m_pChImage->getSize().y);
	m_pChImage->setBrightness(vec3i{ 200, 200, 200 });
	this->addChild(m_pChImage);

	m_pDescLabel = new CLabel("", 20, DX_FONTTYPE_NORMAL, GetColor(250, 250, 177), 0, 10);
	m_pDescLabel->setPosition(850, 200);
	this->addChild(m_pDescLabel);

	int TopY = 128, MidX = GRAPH_SIZE_X * 0.382;
	this->addChild(new CLine2D({ MidX, TopY }, { MidX, GRAPH_SIZE_Y - 50 }, 0x222222), -1);
	this->addChild(new CBox2D(recti{ 50, TopY, 1820, GRAPH_SIZE_Y - TopY - 50 }, 0x222222, false), -1);

	m_MagicCircles.emplace_back(new CPlane({ 80, 1000, 300 }, { 1, -1, 0.7 }, { 1024, 1024 }, 0, "magic_circle.png", { 177, 250, 250, 40 }));
	m_MagicCircles.emplace_back(new CPlane({ 1400, 500, 300 }, { 1, 1, 0.7 }, { 1800, 1800 }, 0, "magic_circle.png", { 247, 135, 135, 40 }));
	for (auto pMagicCircle : m_MagicCircles) this->addChild(pMagicCircle, -2);

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::__updateSelectedLabel()
{
	bool IndexChanged = false;
	if (checkHit(GAME_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (checkHit(GAME_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_select_00.wav"), DX_PLAYTYPE_BACK));

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

	m_pFlagSprite->setPosition(m_pFlagSprite->getPosition().x, m_MenuLabels[m_SelectedLabelIndex]->getPosition().y - 10);
}