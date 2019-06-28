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

		virtual bool initV() { return true; }
		virtual void updateV(double vDeltaTime) override { CNode::updateV(vDeltaTime); }
		virtual void destroyV() { this->removeAllChilds(); }
	};
}