#include <algorithm>
#include "node.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CNode::drawV()
{
	//std::sort(_Childs.begin(), _Childs.end(), [](const CNode* p1, const CNode* p2) { return p1->getLocalZ() < p2->getLocalZ(); });
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
	if (vDestroyChilds) { for (auto pChild : _Childs) delete pChild; }
	_Childs.clear();
}

//***********************************************************************************************
//FUNCTION:
void CNode::removeChild(CNode* vNode, bool vDestroyChild /*= true*/)
{
	_Childs.remove(vNode);
	if (vDestroyChild) delete vNode;
}