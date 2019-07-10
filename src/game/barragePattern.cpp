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
	if (vCounter % 10 != 0) return;

	for (int i = 0; i < 360; i += 10)
	{
		CBullet* pBullet = new CBullet("bullet_00.png", recti{ 416, 128, 32, 32 });
		pBullet->_MoveFunc = CMovePattern::movePattern001;
		pBullet->_Rotation = (i + vCounter) * PI / 180;
		pBullet->_Position.x = x + 10 * sin(pBullet->_Rotation);
		pBullet->_Position.y = y - 10 * cos(pBullet->_Rotation);
		pBullet->_Speed = 3.0;
		CBarrageManager::getInstance()->addBullet(pBullet);
	}
}