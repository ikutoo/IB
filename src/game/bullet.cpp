#include "stdafx.h"
#include "bullet.h"

//*********************************************************************
//FUNCTION:
CBullet::CBullet(const std::string& vImageFile, const recti& vRect) :CSprite(vImageFile, vRect)
{
	this->setAnchor(getSize() / 2);
}