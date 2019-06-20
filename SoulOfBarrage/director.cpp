#include "stdafx.h"
#include "director.h"
#include "inputManager.h"
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
	m_pActiveScene->updateV(deltaTime);

	if (m_DisplayFPS) __drawFPS();
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
void CDirector::__drawFPS()
{
	char Buf[64];
	sprintf(Buf, "FPS: %6.1f", m_FPS);
	SetFontSize(20);
	DrawString(10, 10, Buf, 0x00ff00);
}