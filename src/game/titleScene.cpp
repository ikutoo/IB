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
#include "engine/jsonUtil.h"

using namespace DxEngine;

namespace
{
	const vec3i MENU_COLOR_NORMAL = { 100, 100, 100 };
	const vec3i MENU_COLOR_SELECTED = { 255, 255, 255 };
}

//*********************************************************************
//FUNCTION:
bool CTitleScene::_initV()
{
	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));
	CHECK_RESULT(DxLib::ChangeFont("simkai"));

	m_pParticles = new CParticle01(recti{ 0, 0, GRAPH_SIZE_X, GRAPH_SIZE_Y }, 2.0);
	this->addChild(m_pParticles);

	CJsonReader JsonReader("title_scene.ui");
	auto pUIRoot = JsonReader.getRootNode();
	this->addChild(pUIRoot);

	m_MenuLabels.push_back(dynamic_cast<CLabel*>(pUIRoot->findChild("playLabel")));
	m_MenuLabels.push_back(dynamic_cast<CLabel*>(pUIRoot->findChild("helpLabel")));
	m_MenuLabels.push_back(dynamic_cast<CLabel*>(pUIRoot->findChild("exitLabel")));
	m_pFlagSprite = dynamic_cast<CSprite*>(pUIRoot->findChild("flagSprite"));

	CHECK_RESULT(DxLib::PlayMusic(LOCATE_FILE("bgm_01.mp3"), DX_PLAYTYPE_BACK));

	return true;
}

//*********************************************************************
//FUNCTION:
void CTitleScene::_updateV(double vDeltaTime)
{
	m_pParticles->updateV();

	m_pFlagSprite->setPosition(m_MenuLabels[m_SelectedLabelIndex]->getPosition().x - 100, m_MenuLabels[m_SelectedLabelIndex]->getPosition().y);

	bool IndexChanged = false;
	if (CHECK_HIT_KEY(KEY_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (CHECK_HIT_KEY(KEY_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_select_00.wav"), DX_PLAYTYPE_BACK));

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		if (i == m_SelectedLabelIndex)
			m_MenuLabels[i]->setBrightness(MENU_COLOR_SELECTED);
		else
			m_MenuLabels[i]->setBrightness(MENU_COLOR_NORMAL);
	}

	if (CHECK_HIT_KEY(KEY_INPUT_Z))
	{
		switch (m_SelectedLabelIndex)
		{
		case 0:
			CEngine::getInstance()->pushScene(this);
			CEngine::getInstance()->setActiveScene(new CLevelScene);
			break;
		case 1:
			CEngine::getInstance()->pushScene(this);
			CEngine::getInstance()->setActiveScene(new CHelpScene);
			break;
		case 2:
			CEngine::getInstance()->stop();
			break;
		default:
			_ASSERT(false);
			break;
		}

		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_ok_00.wav"), DX_PLAYTYPE_BACK));
	}

	if (CHECK_HIT_KEY(KEY_INPUT_X))
	{
		m_SelectedLabelIndex = m_MenuLabels.size() - 1;
		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_cancel_00.wav"), DX_PLAYTYPE_BACK));
	}
}

//***********************************************************************************************
//FUNCTION:
void CTitleScene::_destroyV()
{
	CHECK_RESULT(DxLib::StopMusic());
}