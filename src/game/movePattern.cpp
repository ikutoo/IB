#include "stdafx.h"
#include "movePattern.h"
#include "barrageManager.h"
#include "bullet.h"

//*********************************************************************
//FUNCTION:
void CMovePattern::movePattern000(CBullet* vioBullet)
{
	if (vioBullet->_Counter == 0) return;
	vioBullet->_Position.x += vioBullet->_Speed * sin(vioBullet->_Rotation);
	vioBullet->_Position.y -= vioBullet->_Speed * cos(vioBullet->_Rotation);
}

//*********************************************************************
//FUNCTION:
void CMovePattern::movePattern001(CBullet* vioBullet)
{
	if (vioBullet->_Counter == 0) return;

	auto PlayerPos = CBarrageManager::getInstance()->getPlayerPosition();
	vioBullet->_Position.x = PlayerPos.x;
	vioBullet->_Position.y -= vioBullet->_Speed;
}