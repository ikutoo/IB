#include "graphics2d.h"
#include <DXLib/DxLib.h>
#include "common.h"

//*********************************************************************
//FUNCTION:
void DxEngine::CBox2D::drawV()
{
	CNode::drawV();
	CHECK_RESULT(DxLib::DrawBox(m_Rect.x, m_Rect.y, m_Rect.x + m_Rect.w, m_Rect.y + m_Rect.h, m_Color, m_Fill));
}