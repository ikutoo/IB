#include "sprite.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

CSprite::CSprite(const std::string& vImageFile) : m_ImageFile(vImageFile)
{
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERTE(m_ImageHandle != -1);
}

CSprite::~CSprite()
{
	CResourceManager::getInstance()->deleteImage(m_ImageFile);
}

//*********************************************************************
//FUNCTION:
void CSprite::drawV()
{
	CHECK_RESULT(DxLib::DrawGraph(_Position.x, _Position.y, m_ImageHandle, TRUE));
}