#include "stdafx.h"
#include "common.h"
#include "titleScene.h"
#include "utility.h"
#include "inputManager.h"
#include "director.h"

//*********************************************************************
//FUNCTION:
bool CTitleScene::initV()
{
	if (!CScene::initV()) return false;

	ASSERT_SUCCESS(ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE));

	m_TitleLabel = { "Infinite Barrage", 530, 200, 100, 6, 0xffffff, 0xffff00 };
	m_FlagLabel = { "->", 800, 600, 40, 1, 0xffffff, 0x00aa00 };

	SLabel MenuLabel = { "开始游戏", 870, 600, 40, 2, 0xffffff, 0xaaaaaa };
	m_MenuLabels.emplace_back(MenuLabel);

	MenuLabel.pText = "操作说明";
	MenuLabel.y += 100;
	m_MenuLabels.emplace_back(MenuLabel);

	MenuLabel.pText = "退出游戏";
	MenuLabel.y += 100;
	m_MenuLabels.emplace_back(MenuLabel);

	return true;
}

//*********************************************************************
//FUNCTION:
void CTitleScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__drawUI();
	__handleInput();
}

//***********************************************************************************************
//FUNCTION:
void CTitleScene::destroyV()
{
	CScene::destroyV();
}

//*********************************************************************
//FUNCTION:
void CTitleScene::__drawUI()
{
	utility::drawLabel(m_TitleLabel);

	m_FlagLabel.y = m_MenuLabels[m_SelectedLabelIndex].y;
	utility::drawLabel(m_FlagLabel);

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		auto MenuLabel = m_MenuLabels[i];
		if (i == m_SelectedLabelIndex) MenuLabel.edgeColor = 0x00aa00;
		utility::drawLabel(MenuLabel);
	}
}

//*********************************************************************
//FUNCTION:
void CTitleScene::__handleInput()
{
	if (1 == GET_KEY_STATE(KEY_INPUT_DOWN)) m_SelectedLabelIndex++;
	else if (1 == GET_KEY_STATE(KEY_INPUT_UP)) m_SelectedLabelIndex--;

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

	if (CheckHitKey(KEY_INPUT_Z))
	{
		switch (m_SelectedLabelIndex)
		{
		case 0: //开始游戏
			CDirector::getInstance()->setActiveScene(GAME_SCENE_01);
			break;
		case 1: //操作说明
			CDirector::getInstance()->setActiveScene(HELP_SCENE);
			break;
		case 2: //退出游戏
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}
}