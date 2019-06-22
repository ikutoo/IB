#include "stdafx.h"
#include "director.h"
#include "inputManager.h"
#include "barrageManager.h"
#include "scene.h"

CDirector::CDirector()
{
}

CDirector::~CDirector()
{
}

//***********************************************************************************************
//FUNCTION:
void CDirector::update()
{
	int deltaTime = GetNowCount() - m_TimeCounter;
	m_FPS = 1000.0 / deltaTime;
	m_TimeCounter = GetNowCount();

	CInputManager::getInstance()->update();
	CBarrageManager::getInstance()->update();

	m_pActiveScene->updateV(deltaTime);

	if (m_DisplayStatus) __drawStatus();
}

//***********************************************************************************************
//FUNCTION:
bool CDirector::setActiveScene(int vSceneID)
{
	if (m_ID2SceneMap.find(vSceneID) == m_ID2SceneMap.end()) return false;

	if (m_pActiveScene) m_pActiveScene->destroyV();
	m_pActiveScene = m_ID2SceneMap[vSceneID];
	if (!m_pActiveScene->initV()) return false;

	return true;
}

//*********************************************************************
//FUNCTION:
void CDirector::__drawStatus()
{
	CHECK_RESULT(DxLib::SetFontSize(20));

	char Buf[64];
	unsigned int Color = 0x00ff00;
	sprintf(Buf, "FPS: %6.1f", m_FPS);
	CHECK_RESULT(DxLib::DrawString(10, 10, Buf, Color));

	sprintf(Buf, "Bullet Num: %i", CBarrageManager::getInstance()->getNumBullets());
	CHECK_RESULT(DxLib::DrawString(10, 60, Buf, Color));
}