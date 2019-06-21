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

	m_TitleLabel.image = LoadGraph("../Resource/images/title.png");
	int ImgWidth, ImgHeight;
	CHECK_RESULT(GetGraphSize(m_TitleLabel.image, &ImgWidth, &ImgHeight));
	m_TitleLabel.x = (WIDTH - ImgWidth) / 2;
	m_TitleLabel.y = 100;

	SImageLabel MenuLabel = {};
	MenuLabel.image = LoadGraph("../Resource/images/play.png");
	CHECK_RESULT(GetGraphSize(MenuLabel.image, &ImgWidth, &ImgHeight));
	MenuLabel.x = (WIDTH - ImgWidth) / 2;
	MenuLabel.y = 600;
	m_MenuLabels.emplace_back(MenuLabel);

	MenuLabel.image = LoadGraph("../Resource/images/help.png");
	MenuLabel.y += 100;
	m_MenuLabels.emplace_back(MenuLabel);

	MenuLabel.image = LoadGraph("../Resource/images/exit.png");
	MenuLabel.y += 100;
	m_MenuLabels.emplace_back(MenuLabel);

	m_FlagLabel = { "->", 800, 600, 40, 1, 0xffffff, 0x00aa00 };

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
	DrawGraph(m_TitleLabel.x, m_TitleLabel.y, m_TitleLabel.image, TRUE);

	m_FlagLabel.y = m_MenuLabels[m_SelectedLabelIndex].y;
	utility::drawLabel(m_FlagLabel);

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		auto MenuLabel = m_MenuLabels[i];
		DrawGraph(MenuLabel.x, MenuLabel.y, MenuLabel.image, TRUE);
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
			CDirector::getInstance()->setActiveScene(GAME_SCENE);
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