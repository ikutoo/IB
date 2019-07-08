#include "stdafx.h"
#include "player.h"

using namespace DxEngine;

CPlayer::CPlayer()
{
	this->setImageFile("player_00.png", recti{ 0, 0, 64, 96 });
}

CPlayer::~CPlayer()
{
}