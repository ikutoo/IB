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
	//if (vCounter % 2 != 0) return;

	for (int i = 0; i < 360; i += 6)
	{
		CBullet* pBullet = new CBullet("bullet01.png");
		pBullet->_Position.x = x;
		pBullet->_Position.y = y;
		pBullet->_MoveFunc = CMovePattern::movePattern001;
		pBullet->_Angle = (i + vCounter) * PI / 180;
		pBullet->_Speed = 5.0;
		CBarrageManager::getInstance()->addBullet(pBullet);
	}
}