#pragma once
#include <functional>
#include <vector>
#include <map>
#include "common.h"

namespace DxEngine
{
	class CScene;

	class CEngine
	{
	public:
		SINGLETION(CEngine);

		int run();

		void registerPreInitFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_PreInitFuncs.emplace_back(vFunc); }
		void registerInitFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_InitFuncs.emplace_back(vFunc); }
		void registerUpdateFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_UpdateFuncs.emplace_back(vFunc); }

		bool setActiveScene(CScene* vScene);

		void displayStatus(bool vValue) { m_DisplayStatus = vValue; }

	private:
		CEngine() = default;
		~CEngine() = default;

		CScene* m_pActiveScene = nullptr;
		std::map<int, CScene*> m_ID2SceneMap;

		std::vector<std::function<void()>> m_PreInitFuncs;
		std::vector<std::function<void()>> m_InitFuncs;
		std::vector<std::function<void()>> m_UpdateFuncs;

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