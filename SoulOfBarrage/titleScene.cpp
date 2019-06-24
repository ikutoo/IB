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

	CHECK_RESULT(DxLib::SetBackgroundColor(50, 50, 50));

	m_BgImageLabel = { 1100, 150, DxLib::LoadGraph(LOCATE_IMAGE("bg_01.png")) };

	m_TitleLabel.image = DxLib::LoadGraph(LOCATE_IMAGE("title.png"));
	int ImgWidth, ImgHeight;
	CHECK_RESULT(DxLib::GetGraphSize(m_TitleLabel.image, &ImgWidth, &ImgHeight));
	m_TitleLabel.x = (WIDTH - ImgWidth) / 2;
	m_TitleLabel.y = 100;

	SImageLabel MenuLabel;
	MenuLabel.image = DxLib::LoadGraph(LOCATE_IMAGE("play.png"));
	CHECK_RESULT(DxLib::GetGraphSize(MenuLabel.image, &ImgWidth, &ImgHeight));
	MenuLabel.x = (WIDTH - ImgWidth) / 2;
	MenuLabel.y = 600;
	m_MenuLabels.emplace_back(MenuLabel);

	MenuLabel.image = DxLib::LoadGraph(LOCATE_IMAGE("help.png"));
	MenuLabel.y += 100;
	m_MenuLabels.emplace_back(MenuLabel);

	MenuLabel.image = DxLib::LoadGraph(LOCATE_IMAGE("exit.png"));
	MenuLabel.y += 100;
	m_MenuLabels.emplace_back(MenuLabel);

	m_FlagLabel = { 750, m_MenuLabels[0].y, DxLib::LoadGraph(LOCATE_IMAGE("flag.png")) };

	CHECK_RESULT(DxLib::PlayMusic(LOCATE_SOUND("bgm_01.mp3"), DX_PLAYTYPE_LOOP));

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
	CHECK_RESULT(DxLib::StopMusic());
	CHECK_RESULT(DxLib::DeleteGraph(m_BgImageLabel.image));
	CHECK_RESULT(DxLib::DeleteGraph(m_TitleLabel.image));
	CHECK_RESULT(DxLib::DeleteGraph(m_FlagLabel.image));
	for (auto Label : m_MenuLabels) CHECK_RESULT(DxLib::DeleteGraph(Label.image));
	m_MenuLabels.clear();

	CScene::destroyV();
}

//*********************************************************************
//FUNCTION:
void CTitleScene::__drawUI()
{
	DxLib::DrawGraph(m_BgImageLabel.x, m_BgImageLabel.y, m_BgImageLabel.image, TRUE);

	DxLib::DrawGraph(m_TitleLabel.x, m_TitleLabel.y, m_TitleLabel.image, TRUE);

	m_FlagLabel.y = m_MenuLabels[m_SelectedLabelIndex].y + 10;
	DxLib::DrawGraph(m_FlagLabel.x, m_FlagLabel.y, m_FlagLabel.image, TRUE);

	for (int i = 0; i < m_MenuLabels.size(); ++i)
	{
		auto MenuLabel = m_MenuLabels[i];
		DxLib::DrawGraph(MenuLabel.x, MenuLabel.y, MenuLabel.image, TRUE);
	}
}

//*********************************************************************
//FUNCTION:
void CTitleScene::__handleInput()
{
	bool IndexChanged = false;
	if (1 == GET_KEY_STATE(KEY_INPUT_DOWN)) { m_SelectedLabelIndex++; IndexChanged = true; }
	else if (1 == GET_KEY_STATE(KEY_INPUT_UP)) { m_SelectedLabelIndex--; IndexChanged = true; }

	if (IndexChanged) CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_SOUND("se_select_01.mp3"), DX_PLAYTYPE_NORMAL));

	if (m_SelectedLabelIndex < 0) m_SelectedLabelIndex = m_MenuLabels.size() - 1;
	else if (m_SelectedLabelIndex >= m_MenuLabels.size()) m_SelectedLabelIndex = 0;

	if (DxLib::CheckHitKey(KEY_INPUT_Z) || DxLib::CheckHitKey(KEY_INPUT_RETURN))
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
			_ASSERT(false);
			break;
		}

		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_SOUND("se_ok_01.mp3"), DX_PLAYTYPE_NORMAL));
	}
}