#include "renderTarget.h"
#include <DXLib/DxLib.h>
#include "common.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
CRenderTarget::CRenderTarget(int vWidth, int vHeight)
{
	m_GraphHandle = DxLib::MakeScreen(vWidth, vHeight, TRUE);
	_ASSERTE(m_GraphHandle != -1);
}

//*********************************************************************
//FUNCTION:
CRenderTarget::~CRenderTarget()
{
	CHECK_RESULT(DxLib::DeleteGraph(m_GraphHandle));
}

//*********************************************************************
//FUNCTION:
void CRenderTarget::drawV()
{
	CHECK_RESULT(DxLib::DrawGraph(0, 0, m_GraphHandle, TRUE));
}