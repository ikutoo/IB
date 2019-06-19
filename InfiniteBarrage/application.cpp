#include "stdafx.h"
#include "application.h"
#include "titleScene.h"

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
	delete m_pTitleScene;
}

//*********************************************************************
//FUNCTION:
int CApplication::run()
{
	__init();

	while (0 == __processLoop())
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		m_pTitleScene->update();

		ScreenFlip();
	}

	DxLib_End();

	return EXIT_SUCCESS;
}

//*********************************************************************
//FUNCTION:
void CApplication::__init()
{
	ASSERT_SUCCESS(ChangeWindowMode(TRUE));
	ASSERT_SUCCESS(SetGraphMode(WIDTH, HEIGHT, 32));
	ASSERT_SUCCESS(SetWindowText("IB"));
	ASSERT_SUCCESS(SetBackgroundColor(50, 50, 50));

	ASSERT_SUCCESS(DxLib_Init());
	ASSERT_SUCCESS(SetDrawScreen(DX_SCREEN_BACK));

	m_pTitleScene = new CTitleScene;
	m_pTitleScene->init();
}

//*********************************************************************
//FUNCTION:
int CApplication::__processLoop()
{
	if (0 != ProcessMessage()) return -1;
	if (0 != ClearDrawScreen()) return -1;

	return 0;
}