#include "stdafx.h"
#include "titleScene.h"
#include <thread>
#include "common.h"
#include "levelScene.h"
#include "helpScene.h"
#include "engine/utility.h"
#include "engine/inputManager.h"
#include "engine/engine.h"
#include "engine/resourceManager.h"

using namespace DxEngine;

namespace
{
	const vec3i MENU_COLOR_NORMAL = { 50, 50, 50 };
	const vec3i MENU_COLOR_SELECTED = { 255, 255, 255 };
}

//*********************************************************************
//FUNCTION:
bool CTitleScene::initV()
{
	if (!CScene::initV()) return false;

	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));
	CHECK_RESULT(DxLib::ChangeFont("simkai"));

	auto pBgLabel = new CImageLabel("bg_01.png");
	pBgLabel->setPosition(1100, 100);
	pBgLabel->setSize(800, 1200);
	pBgLabel->setColor(vec3i{ 50, 50, 50 });
	this->addChild(pBgLabel);

	__initPartices();

	auto pTitleLabel = new CImageLabel("title.png");
	pTitleLabel->setPosition((GRAPH_SIZE_X - pTitleLabel->getSize().x) / 2, 100);
	this->addChild(pTitleLabel);

	auto pPlayLabel = new CTextLabel("开始游戏", 50, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 0xffffff, 0xffff00);
	pPlayLabel->setPosition(800, 600);
	m_MenuLabels.emplace_back(pPlayLabel);

	auto pHelpLabel = new CTextLabel("操作说明", 50, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 0xffffff, 0xffff00);
	pHelpLabel->setPosition(800, 700);
	m_MenuLabels.emplace_back(pHelpLabel);

	auto pExitLabel = new CTextLabel("退出游戏", 50, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 0xffffff, 0xffff00);
	pExitLabel->setPosition(800, 800);
	m_MenuLabels.emplace_back(pExitLabel);

	for (auto pLabel : m_MenuLabels) this->addChild(pLabel);

	m_pFlagLabel = new CImageLabel("flag.png");
	this->addChild(m_pFlagLabel);

	CHECK_RESULT(DxLib::PlayMusic(LOCATE_FILE("bgm_01.mp3"), DX_PLAYTYPE_BACK));

	return true;
}

//*********************************************************************
//FUNCTION:
void CTitleScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__updateParticles();

	m_pFlagLabel->setPosition(m_MenuLabels[m_SelectedLabelIndex]->getPosition().x - 100, m_MenuLabels[m_SelectedLabelIndex]->getPosition().y);

	bool IndexChanged = false;
	if (CHECK_HIT_KEY(KEY_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (CHECK_HIT_KEY(KEY_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_select_01.mp3"), DX_PLAYTYPE_BACK));

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		if (i == m_SelectedLabelIndex)
			m_MenuLabels[i]->setColor(MENU_COLOR_SELECTED);
		else
			m_MenuLabels[i]->setColor(MENU_COLOR_NORMAL);
	}

	if (CHECK_HIT_KEY(KEY_INPUT_Z) || CHECK_HIT_KEY(KEY_INPUT_RETURN))
	{
		switch (m_SelectedLabelIndex)
		{
		case 0:
			CEngine::getInstance()->setActiveScene(new CLevelScene);
			break;
		case 1:
			CEngine::getInstance()->setActiveScene(new CHelpScene);
			break;
		case 2:
			CEngine::getInstance()->end();
			break;
		default:
			_ASSERT(false);
			break;
		}

		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_ok_01.mp3"), DX_PLAYTYPE_BACK));
	}
}

//***********************************************************************************************
//FUNCTION:
void CTitleScene::destroyV()
{
	CHECK_RESULT(DxLib::StopMusic());

	CScene::destroyV();
}

//*********************************************************************
//FUNCTION:
void CTitleScene::__initPartices()
{
	for (int i = 0; i < 400; ++i)
	{
		CSprite* pParticle = new CSprite("bullet01.png");
		pParticle->setScale(0.3 + 0.3 * randf(), 0.3 + 0.3 * randf());
		pParticle->setColor(vec3i{ 100 + rand() % 50, 100 + rand() % 50, 0 });
		float PosX = rand() % GRAPH_SIZE_X;
		float PosY = rand() % GRAPH_SIZE_Y + GRAPH_SIZE_Y;
		pParticle->setPosition(vec2f{ PosX, PosY });

		float SpeedX = -0.2 + 0.4 * randf();
		float SpeedY = -0.3 - 0.2 * randf();

		m_Particles.emplace_back(SParticle{ pParticle, SpeedX, SpeedY });
		this->addChild(pParticle);
	}
}

//*********************************************************************
//FUNCTION:
void CTitleScene::__updateParticles()
{
	for (auto pParticle : m_Particles)
	{
		if (_Counter % 100 == 0) pParticle.SpeedX = -0.2 + 0.4 * randf();
		float PosX = pParticle.pSprite->getPosition().x + pParticle.SpeedX;
		float PosY = pParticle.pSprite->getPosition().y + pParticle.SpeedY;

		if (PosY < 0) { PosX = rand() % GRAPH_SIZE_X; PosY = GRAPH_SIZE_Y; };

		pParticle.pSprite->setPosition(PosX, PosY);
	}
}