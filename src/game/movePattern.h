#pragma once

class CBullet;

class CMovePattern
{
public:
	static void movePattern000(CBullet* vioBullet);		//向前直线匀速移动
	static void movePattern001(CBullet* vioBullet);		//跟随自机向前发射
};