#include "stdafx.h"
#include "collision.h"
#include <DXLib/DxLib.h>
#include "engine/common.h"
#include "common.h"

const int IMAGE_SIZE = 63;
const int PLAYER_HIT_DISTANCE = 3;
const int PLAYER_GRAZE_DISTANCE = 21;

//*****************************************************************
//FUNCTION:
CCollisionDetector::CCollisionDetector()
{
	m_BarrageSoftImage = MakeARGB8ColorSoftImage(IMAGE_SIZE, IMAGE_SIZE);
	_ASSERTE(m_BarrageSoftImage != -1);
}

//*****************************************************************
//FUNCTION:
CCollisionDetector::~CCollisionDetector()
{
	CHECK_RESULT(DxLib::DeleteSoftImage(m_BarrageSoftImage));
}

//*****************************************************************
//FUNCTION:
void CCollisionDetector::detectCollision(vec2f vPlayerPosition, int vGraphHandle)
{
	m_IsPlayerHit = false;
	m_IsPlayerGrazed = false;

	CHECK_RESULT(DxLib::SetDrawScreen(vGraphHandle));

	int x1 = max(0, vPlayerPosition.x - IMAGE_SIZE / 2);
	int y1 = max(0, vPlayerPosition.y - IMAGE_SIZE / 2);
	int x2 = min(vPlayerPosition.x + IMAGE_SIZE / 2 + 1, GRAPH_SIZE_X);
	int y2 = min(vPlayerPosition.y + IMAGE_SIZE / 2 + 1, GRAPH_SIZE_Y);
	GetDrawScreenSoftImage(x1, y1, x2, y2, m_BarrageSoftImage);

	for (int x = 0; x < IMAGE_SIZE; ++x)
	{
		for (int y = 0; y < IMAGE_SIZE; ++y)
		{
			int r, g, b, a;
			GetPixelSoftImage(m_BarrageSoftImage, x, y, &r, &g, &b, &a);

			const int COLLISION_ALPHA_THRESHOLD = 20;
			if (a > COLLISION_ALPHA_THRESHOLD)
			{
				float Distance = distance(vec2f{ IMAGE_SIZE / 2, IMAGE_SIZE / 2 }, vec2f{ (float)x, (float)y });
				if (Distance <= PLAYER_HIT_DISTANCE) m_IsPlayerHit = true;
				else if (Distance <= PLAYER_GRAZE_DISTANCE) m_IsPlayerGrazed = true;
			}
		}

		if (m_IsPlayerHit) break;
	}

	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));
}