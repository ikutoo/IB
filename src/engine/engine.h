#pragma once
#include <functional>
#include <vector>
#include <stack>
#include <map>
#include "common.h"
#include "cpuTimer.h"

namespace DxEngine
{
	class CScene;

	class CEngine
	{
	public:
		SINGLETION(CEngine);

		int		run();
		void	stop() { m_IsMainLoopDone = true; }

		void registerInitFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_InitFuncs.emplace_back(vFunc); }
		void registerUpdateFunc(std::function<void()> vFunc) { _ASSERTE(vFunc); m_UpdateFuncs.emplace_back(vFunc); }

		bool setActiveScene(CScene* vScene);
		void pushScene(CScene* vScene);
		CScene* popScene();

		void setWindowSize(int vWidth, int vHeight) { _ASSERTE(!m_IsInitialized); m_DisplayInfo.WindowSize = { vWidth, vHeight }; }
		void setFullscreen(bool vFullscreen) { m_DisplayInfo.IsFullscreen = vFullscreen; }
		void setWindowPosition(int vPosX, int vPosY) { _ASSERTE(!m_IsInitialized); m_DisplayInfo.WindowPosition = { vPosX, vPosY }; }
		void setWindowTitle(const std::string& vTitle) { _ASSERTE(!m_IsInitialized); m_DisplayInfo.WindowTitle = vTitle; }
		void setGraphSize(int vWidth, int vHeight) { _ASSERTE(!m_IsInitialized); m_GraphSize = { vWidth, vHeight }; }
		void setExpectedFPS(float vExpectedFPS) { m_ExpectedFPS = vExpectedFPS; }
		void setDisplayStatusHint() { m_DisplayStatusHint = true; }
		void setShowConsoleHint() { m_ShowConsoleHint = true; }
		void setDisableCNInputHint() { m_DisableCNInputHint = true; }

		float getFPS() const { m_FPS; }
		vec2i getGraphSize() const { return m_GraphSize; }
		bool  isFullScreen() const { return m_DisplayInfo.IsFullscreen; }

		void updateStatus(const std::string& vDesc, float vValue) { m_AppStatusMap[vDesc] = vValue; }

	private:
		CEngine() = default;
		~CEngine() = default;

		std::stack<CScene*> m_CachedScenes;
		CScene* m_pActiveScene = nullptr;
		std::map<int, CScene*> m_ID2SceneMap;

		std::vector<std::function<void()>> m_InitFuncs;
		std::vector<std::function<void()>> m_UpdateFuncs;

		vec2i m_GraphSize = {};
		SDisplayInfo m_DisplayInfo = {};

		std::map<std::string, float> m_AppStatusMap;

		CCPUTimer	m_Timer;
		double		m_CurrentTime = 0.0;

		bool	m_IsInitialized = false;
		bool	m_IsMainLoopDone = false;
		bool	m_DisplayStatusHint = false;
		bool	m_ShowConsoleHint = false;
		bool	m_DisableCNInputHint = false;
		float	m_FPS = 0.0;
		float	m_ExpectedFPS = 60.0;

		void __drawStatus();

		bool __init();
		void __update();
		void __render();
		void __destroy();

		bool __initWindowInfo();
		double __updateFPS();
		void __allocConsoleIfNeccessary();
		void __freeConsoleIfNecessary();
	};
}