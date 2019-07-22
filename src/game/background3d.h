#pragma once
#include "engine/sprite.h"

class CBackground3d : public DxEngine::CNode
{
public:
	struct SVtPm
	{
		float x, y;
		float u, v;
	};

	struct SObject
	{
		int Type;			// 0:与画面平行、1:与画面垂直
		int Img;
		float x, y, z;		//中心点
		float LargeX, LargeY;
		float u, v;
		float FromZ, ToZ;
		float FadeFromZ, FadeToZ;
		DxLib::VERTEX_3D Vertex[6];
	};

	CBackground3d();
	~CBackground3d() {}

	void updateV(double vDeltaTime) override;
	void drawV() override;

private:
	SObject m_Object = {};
};