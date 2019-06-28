#include "stdafx.h"
#include "sprite.h"
#include "commonMicro.h"

using namespace DxEngine;

std::map<std::string, int> CSprite::m_ImageFile2HandleMap = {};

CSprite::CSprite(const std::string& vImageFile)
{
	if (!vImageFile.empty())
	{
		if (m_ImageFile2HandleMap.find(vImageFile) != m_ImageFile2HandleMap.end())
		{
			m_ImageHandle = m_ImageFile2HandleMap[vImageFile];
		}
		else
		{
			m_ImageHandle = DxLib::LoadGraph(vImageFile.c_str());
			_ASSERTE(m_ImageHandle != -1);
			m_ImageFile2HandleMap[vImageFile] = m_ImageHandle;
		}
	}
}

//*********************************************************************
//FUNCTION:
void CSprite::drawV()
{
	if (m_ImageHandle != -1)
	{
		CHECK_RESULT(DxLib::DrawGraph(_Position.x, _Position.y, m_ImageHandle, TRUE));
	}
}