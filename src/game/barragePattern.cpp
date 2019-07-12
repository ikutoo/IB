
#include "stdafx.h"
#include "common.h"
#include "barragePattern.h"
#include "movePattern.h"
#include "barrageManager.h"
#include "bullet.h"

//*********************************************************************
//FUNCTION:
void CBarragePattern::playerBarrage00(float x, float y, int vCounter)
{
	if (vCounter % 5 != 0) return;

	auto pBullet = new CBullet("player_00.png", recti{ 0, 288, 128, 32 });

	pBullet->_MoveFunc = CMovePattern::movePattern000;
	pBullet->_Position = { x, y };
	pBullet->_Speed = 30.0;
	pBullet->setAnchor(vec2i{ 0, pBullet->getSize().y / 2 });
	pBullet->setImageRotation(-PI / 2);

	CBarrageManager::getInstance()->addBullet(pBullet, true);
}

//*********************************************************************
//FUNCTION:
void CBarragePattern::playerBarrage01(float x, float y, int vCounter)
{
	auto pBullet = new CBullet("player_00.png", recti{ 0, 448, 512, 64 });

	pBullet->_MoveFunc = CMovePattern::movePattern001;
	pBullet->_Scale = { 0.3, 0.3 };
	pBullet->_Position.x = x;
	pBullet->_Position.y = y + abs(vCounter % 64 - 32);
	pBullet->_Speed = 153.6;
	pBullet->setAnchor(vec2i{ 0, pBullet->getSize().y / 2 });
	pBullet->setImageRotation(-PI / 2);

	CBarrageManager::getInstance()->addBullet(pBullet, true);
}

//*********************************************************************
//FUNCTION:
void CBarragePattern::enemyBarrage000(float x, float y, int vCounter)
{
	if (vCounter % 10 != 0) return;

	for (int i = 0; i < 360; i += 10)
	{
		CBullet* pBullet = new CBullet("bullet_00.png", recti{ 416, 128, 32, 32 });
		pBullet->_MoveFunc = CMovePattern::movePattern000;
		pBullet->_Rotation = (i + vCounter) * PI / 180;
		pBullet->_Position.x = x + 10 * sin(pBullet->_Rotation);
		pBullet->_Position.y = y - 10 * cos(pBullet->_Rotation);
		pBullet->_Speed = 3.0;
		CBarrageManager::getInstance()->addBullet(pBullet);
	}
}