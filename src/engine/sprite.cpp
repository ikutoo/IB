#include "sprite.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

CSprite::CSprite(const std::string& vImageFile)
{
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERTE(m_ImageHandle != -1);
}

//*********************************************************************
//FUNCTION:
void CSprite::drawV()
{
	CHECK_RESULT(DxLib::DrawGraph(_Position.x, _Position.y, m_ImageHandle, TRUE));
}