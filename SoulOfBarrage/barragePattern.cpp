#include "stdafx.h"
#include "common.h"
#include "barragePattern.h"
#include "barrageManager.h"

//*********************************************************************
//FUNCTION:
void barrage_pattern::barragePattern001(int x, int y, int vCounter)
{
	//if (vCounter % 2 != 0) return;

	for (int i = 0; i < 360; i += 6)
	{
		SBullet Bullet;
		Bullet.x = x;
		Bullet.y = y;
		Bullet.bulletType = 1;
		Bullet.movePattern = 1;
		Bullet.angle = (i + vCounter) * PI / 180;
		Bullet.speed = 5.0;
		CBarrageManager::getInstance()->addBullet(Bullet);
	}
}