#pragma once
#include "node.h"

namespace DxEngine
{
	class CRenderTarget : public CNode
	{
	public:
		CRenderTarget(int vWidth, int vHeight);
		~CRenderTarget();

		virtual void drawV() override;

		int getRenderGraph() const { return m_GraphHandle; }

	private:
		int m_GraphHandle = -1;
	};
}