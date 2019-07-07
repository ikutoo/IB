#include "node.h"
#include <algorithm>
#include <DXLib/DxLib.h>

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CNode::drawV()
{
	DxLib::SetDrawBright(_BrightnessColor.x, _BrightnessColor.y, _BrightnessColor.z);

	_Childs.sort([](const CNode* l, const CNode* r) {return l->getLocalZ() < r->getLocalZ(); });
	for (auto pChild : _Childs) pChild->drawV();
}

//*********************************************************************
//FUNCTION:
void CNode::updateV(double vDeltaTime)
{
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