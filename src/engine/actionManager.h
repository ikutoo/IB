#pragma once
#include <vector>
#include <map>
#include "common.h"
#include "action.h"

namespace DxEngine
{
	class CActionManager
	{
	public:
		SINGLETION(CActionManager);

		void startAction(CAction* vAction, bool vStopPrevActions = true);

		void update();

	private:
		CActionManager() = default;
		~CActionManager() = default;

		std::map<CNode*, std::vector<CAction*>> m_Node2ActionMap;
	};
}