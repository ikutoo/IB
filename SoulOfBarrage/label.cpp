#include "stdafx.h"
#include "label.h"
#include "commonMicro.h"

using namespace DxEngine;

DxEngine::CImageLabel::CImageLabel(int vImageHandle, bool vDeleteImageOnDestroy) : m_ImageHandle(vImageHandle), m_DeleteImageOnDestroy(vDeleteImageOnDestroy)
{
	CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
}

DxEngine::CImageLabel::CImageLabel(const char* vImageFile, bool vDeleteImageOnDestroy) : m_DeleteImageOnDestroy(vDeleteImageOnDestroy)
{
	m_ImageHandle = DxLib::LoadGraph(vImageFile);
	_ASSERT(m_ImageHandle != -1);
	CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
}

DxEngine::CImageLabel::~CImageLabel()
{
	if (m_DeleteImageOnDestroy) CHECK_RESULT(DxLib::DeleteGraph(m_ImageHandle));
}

//*********************************************************************
//FUNCTION:
void DxEngine::CImageLabel::drawV()
{
	CHECK_RESULT(DxLib::DrawGraph(_Position.x, _Position.y, m_ImageHandle, TRUE));
	CNode::drawV();
}