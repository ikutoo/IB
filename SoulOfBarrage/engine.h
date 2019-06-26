#pragma once
#include <functional>
#include <vector>
#include <map>
#include "common.h"

#define Engine DxEngine::CEngine::getInstance()

namespace DxEngine
{
	class CScene;

	class CEngine
	{
	public:
		SINGLETION(CEngine);

		int run();

		void registerInitFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_ExtraInitFuncs.emplace_back(vFunc); }
		void registerUpdateFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_ExtraUpdateFuncs.emplace_back(vFunc); }

		void registerScene(int vSceneID, CScene* vScene) { _ASSERTE(vScene), m_ID2SceneMap[vSceneID] = vScene; }
		bool setActiveScene(int vSceneID);

		void displayStatus(bool vValue) { m_DisplayStatus = vValue; }

	private:
		CEngine() = default;
		~CEngine() = default;

		CScene* m_pActiveScene = nullptr;
		std::map<int, CScene*> m_ID2SceneMap;

		std::vector<std::function<void()>> m_ExtraInitFuncs;
		std::vector<std::function<void()>> m_ExtraUpdateFuncs;

		bool	m_DisplayStatus = false;
		int		m_TimeCounter = 0;
		float	m_FPS = 0.0;

		void __drawStatus();

		bool __init();
		void __update();
		void __render();
		void __destroy();
	};
}