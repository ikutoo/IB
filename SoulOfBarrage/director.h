#pragma once
#include <map>
#include "common.h"

class CScene;

class CDirector
{
public:
	SINGLETION(CDirector);
	DISALLOW_COPY_AND_ASSIGN(CDirector);

	void update();
	void registerScene(int vSceneID, CScene* vScene) { _ASSERTE(vScene && !m_IsInitialized), m_ID2SceneMap[vSceneID] = vScene; }
	bool setActiveScene(int vSceneID);

private:
	CDirector();
	~CDirector();

	bool m_IsInitialized = false;

	CScene* m_pActiveScene = nullptr;
	std::map<int, CScene*> m_ID2SceneMap;
};