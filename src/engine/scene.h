#pragma once
#include <vector>
#include "node.h"

namespace DxEngine
{
	class CScene : public CNode
	{
	public:
		CScene() = default;
		virtual ~CScene() = default;

		bool init();
		void update(double vDeltaTime);
		void destroy();

	protected:
		virtual bool _initV() { return true; }
		virtual void _updateV(double vDeltaTime) {}
		virtual void _destroyV() {}

	private:
		bool m_IsCached = false;
		bool m_IsIntialized = false;

		friend class CEngine;
	};
}