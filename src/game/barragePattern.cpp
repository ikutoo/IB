#include "stdafx.h"
#include "common.h"
#include "barragePattern.h"
#include "movePattern.h"
#include "barrageManager.h"
#include "bullet.h"

//*********************************************************************
//FUNCTION:
void CBarragePattern::playerBarrage00(CBarrage* vOwner, int vCounter)
{
	auto pBullet = new CBullet("player_00.png", recti{ 0, 448, 512, 64 });

	pBullet->_MoveFunc = CMovePattern::movePattern000;
	pBullet->_Scale = { 0.5, 0.5 };
	pBullet->_Speed = 10.0;
	pBullet->setAnchor(vec2i{ pBullet->getSize().x / 2, pBullet->getSize().y });
	pBullet->setImageRotation(PI / 2);

	vOwner->addBullet(pBullet);
}

//*********************************************************************
//FUNCTION:
void CBarragePattern::enemyBarrage000(CBarrage* vOwner, int vCounter)
{
	if (vCounter % 10 != 0) return;

	for (int i = 0; i < 360; i += 10)
	{
		CBullet* pBullet = new CBullet("bullet_00.png", recti{ 416, 128, 32, 32 });
		pBullet->_MoveFunc = CMovePattern::movePattern000;
		pBullet->_Rotation = (i + vCounter) * PI / 180;
		pBullet->_Position.x = 20 * sin(pBullet->_Rotation);
		pBullet->_Position.y = -20 * cos(pBullet->_Rotation);
		pBullet->_Speed = 3.0;
		vOwner->addBullet(pBullet);
	}
}