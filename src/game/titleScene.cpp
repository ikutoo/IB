#include "stdafx.h"
#include "titleScene.h"
#include <thread>
#include "common.h"
#include "levelScene.h"
#include "helpScene.h"
#include "engine/utility.h"
#include "engine/inputManager.h"
#include "engine/engine.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
bool CTitleScene::initV()
{
	if (!CScene::initV()) return false;

	CHECK_RESULT(DxLib::SetBackgroundColor(50, 50, 50));

	auto pBgLabel = new CImageLabel(LOCATE_IMAGE("bg_01.png"));
	pBgLabel->setPosition(1100, 150);
	this->addChild(pBgLabel);

	auto pTitleLabel = new CImageLabel(LOCATE_IMAGE("title.png"));
	pTitleLabel->setPosition((WIDTH - pTitleLabel->getSize().x) / 2, 100);
	this->addChild(pTitleLabel);

	auto pPlayLabel = new CImageLabel(LOCATE_IMAGE("play.png"));
	pPlayLabel->setPosition((WIDTH - pPlayLabel->getSize().x) / 2 - 40, 600);
	m_MenuLabels.emplace_back(pPlayLabel);

	auto pHelpLabel = new CImageLabel(LOCATE_IMAGE("help.png"));
	pHelpLabel->setPosition((WIDTH - pHelpLabel->getSize().x) / 2 - 20, 700);
	m_MenuLabels.emplace_back(pHelpLabel);

	auto pExitLabel = new CImageLabel(LOCATE_IMAGE("exit.png"));
	pExitLabel->setPosition((WIDTH - pExitLabel->getSize().x) / 2, 800);
	m_MenuLabels.emplace_back(pExitLabel);

	for (auto pLabel : m_MenuLabels) this->addChild(pLabel);

	m_pFlagLabel = new CImageLabel(LOCATE_IMAGE("flag.png"));
	this->addChild(m_pFlagLabel);

	CHECK_RESULT(DxLib::PlayMusic(LOCATE_SOUND("bgm_01.mp3"), DX_PLAYTYPE_BACK));

	return true;
}

//*********************************************************************
//FUNCTION:
void CTitleScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	m_pFlagLabel->setPosition(m_MenuLabels[m_SelectedLabelIndex]->getPosition().x - 100, m_MenuLabels[m_SelectedLabelIndex]->getPosition().y + 10);

	bool IndexChanged = false;
	if (CHECK_HIT_KEY(KEY_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (CHECK_HIT_KEY(KEY_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_SOUND("se_select_01.mp3"), DX_PLAYTYPE_BACK));

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

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

		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_SOUND("se_ok_01.mp3"), DX_PLAYTYPE_BACK));
	}
}

//***********************************************************************************************
//FUNCTION:
void CTitleScene::destroyV()
{
	CHECK_RESULT(DxLib::StopMusic());

	CScene::destroyV();
}