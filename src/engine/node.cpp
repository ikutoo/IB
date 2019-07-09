#include "node.h"
#include <algorithm>
#include <DXLib/DxLib.h>

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CNode::drawV()
{
	if (_IsPaused || !_IsVisible) return;

	DxLib::SetDrawBright(_BrightnessColor.x, _BrightnessColor.y, _BrightnessColor.z);

	_Childs.sort([](const CNode* l, const CNode* r) {return l->getLocalZ() < r->getLocalZ(); });
	for (auto pChild : _Childs) pChild->drawV();
}

//*********************************************************************
//FUNCTION:
void CNode::updateV(double vDeltaTime)
{
	if (_IsPaused) return;

	_Counter++;
	for (auto pChild : _Childs) pChild->updateV(vDeltaTime);
}

//***********************************************************************************************
//FUNCTION:
void CNode::removeAllChilds(bool vDestroyChilds)
{
	if (vDestroyChilds) { for (auto pChild : _Childs) { pChild->removeAllChilds(); delete pChild; } }
	_Childs.clear();
}

//***********************************************************************************************
//FUNCTION:
void CNode::removeChild(CNode* vNode, bool vDestroyChild /*= true*/)
{
	_Childs.remove(vNode);
	if (vDestroyChild) delete vNode;
}

//*********************************************************************
//FUNCTION:
CNode* CNode::findChild(const std::string& vName)
{
	for (auto pChild : _Childs)
	{
		if (pChild->getName() == vName) return pChild;
	}
	return nullptr;
}

//***********************************************************************************************
//FUNCTION:
void CNode::addChild(CNode* vNode, float vLocalZ)
{
	_ASSERT(vNode);
	if (vLocalZ != 0.0) vNode->setLocalZ(vLocalZ);
	_Childs.emplace_back(vNode);
}