#include "stdafx.h"
#include "movePattern.h"
#include "common.h"

//*********************************************************************
//FUNCTION:
void move_pattern::movePattern001(SBullet& vioBullet)
{
	vioBullet.x += vioBullet.speed * sin(vioBullet.angle);
	vioBullet.y += vioBullet.speed * cos(vioBullet.angle);
}