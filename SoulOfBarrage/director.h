#pragma once
#include <map>
#include "common.h"

class CScene;

class CDirector
{
public:
	SINGLETION(CDirector);

	void update();
	void registerScene(int vSceneID, CScene* vScene) { _ASSERTE(vScene && !m_IsInitialized), m_ID2SceneMap[vSceneID] = vScene; }
	bool setActiveScene(int vSceneID);

	void displayStatus(bool vValue) { m_DisplayStatus = vValue; }

private:
	CDirector();
	~CDirector();

	bool	m_IsInitialized = false;
	bool	m_DisplayStatus = false;
	int		m_TimeCounter = 0;
	float	m_FPS = 0.0;

	CScene* m_pActiveScene = nullptr;
	std::map<int, CScene*> m_ID2SceneMap;

	void __drawStatus();
};