#include "stdafx.h"
#include "player.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CPlayer::updateV(double vDeltaTime)
{
	if (_Counter % 100 == 0) this->setRect(recti{ 256, 0, 64, 96 });
	if (_Counter % 100 == 25) this->setRect(recti{ 256, 0, 64, 96 });
	if (_Counter % 100 == 50) this->setRect(recti{ 256, 0, 64, 96 });
	if (_Counter % 100 == 25) this->setRect(recti{ 256, 0, 64, 96 });
}

//*********************************************************************
//FUNCTION:
void CPlayer::__init()
{
	this->setImageFile("player_00.png", recti{ 256, 0, 64, 96 });
}