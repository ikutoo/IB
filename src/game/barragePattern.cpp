#include "stdafx.h"
#include "common.h"
#include "barragePattern.h"
#include "movePattern.h"
#include "barrageManager.h"
#include "bullet.h"

//*********************************************************************
//FUNCTION:
void CBarragePattern::barragePattern001(float x, float y, int vCounter)
{
	if (vCounter % 4 != 0) return;

	for (int i = 0; i < 360; i += 30)
	{
		CBullet* pBullet = new CBullet("bullet_01.png");
		pBullet->_MoveFunc = CMovePattern::movePattern001;
		pBullet->_Rotation = (i + vCounter) * PI / 180;
		pBullet->_Position.x = x + 20 * sin(pBullet->_Rotation);
		pBullet->_Position.y = y - 20 * cos(pBullet->_Rotation);
		pBullet->_Speed = 5.0;
		CBarrageManager::getInstance()->addBullet(pBullet);
	}
}