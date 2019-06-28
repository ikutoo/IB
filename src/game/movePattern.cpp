#include "stdafx.h"
#include "movePattern.h"
#include "bullet.h"

//*********************************************************************
//FUNCTION:
void CMovePattern::movePattern001(CBullet* vioBullet)
{
	vioBullet->_Position.x += vioBullet->_Speed * sin(vioBullet->_Angle);
	vioBullet->_Position.y += vioBullet->_Speed * cos(vioBullet->_Angle);
}