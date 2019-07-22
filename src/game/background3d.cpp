#include "stdafx.h"
#include "background3d.h"
#include "engine/common.h"
#include "engine/resourceManager.h"
#include "common.h"

using namespace DxEngine;

const CBackground3d::SVtPm VT_PM[6] = { {-1,1,0,0},{1,1,1,0},{-1,-1,0,1},{1,-1,1,1},{-1,-1,0,1},{1,1,1,0} };

//****************************************************
//FUNCTION:
CBackground3d::CBackground3d()
{
	m_Object.Img = CResourceManager::getInstance()->loadImage("kabe.png");
	m_Object.LargeX = 144.0f;
	m_Object.LargeY = 180.0f;
	m_Object.Type = 1;
	m_Object.x = 500;
	m_Object.y = GRAPH_SIZE_Y / 2;
	m_Object.z = 0.0f;
	m_Object.u = 0.763671875f;
	m_Object.v = 1.0f;
	m_Object.FromZ = 200;
	m_Object.FadeFromZ = 100;//描画フェードアウト開始地点
	m_Object.ToZ = -200;

	for (int i = 0; i < 6; i++)
	{
		m_Object.Vertex[i].r = 255;
		m_Object.Vertex[i].b = 255;
		m_Object.Vertex[i].g = 255;
		m_Object.Vertex[i].a = 255;
		m_Object.Vertex[i].u = m_Object.u * VT_PM[i].u;
		m_Object.Vertex[i].v = m_Object.v * VT_PM[i].v;
	}
}

//****************************************************
//FUNCTION:
void CBackground3d::updateV(double vDeltaTime)
{
	CNode::updateV(vDeltaTime);

	switch (m_Object.Type)
	{
	case 0:
		for (int i = 0; i < 6; i++)
		{
			m_Object.Vertex[i].pos.x = m_Object.x + m_Object.LargeX * VT_PM[i].x;
			m_Object.Vertex[i].pos.y = m_Object.y + m_Object.LargeY * VT_PM[i].y;
			m_Object.Vertex[i].pos.z = m_Object.z;
		}
		break;
	case 1:
		for (int i = 0; i < 6; i++)
		{
			m_Object.Vertex[i].pos.x = m_Object.x;
			m_Object.Vertex[i].pos.y = m_Object.y + m_Object.LargeY * VT_PM[i].y;
			m_Object.Vertex[i].pos.z = m_Object.z + m_Object.LargeX * VT_PM[i].x;
		}
		break;
	}

	if (m_Object.FromZ - m_Object.FadeFromZ <= 0)
	{
		printfDx(".Fromの設定がおかしい\n");
	}
	else if (m_Object.FadeToZ - m_Object.ToZ <= 0)
	{
		printfDx(".Toの設定がおかしい\n");
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			float z = m_Object.Vertex[i].pos.z;
			//位置が描画する範囲より遠かったら透過0
			if (z < m_Object.ToZ)
			{
				m_Object.Vertex[i].a = 0;
			}
			//(近づいている場合)フェードインする位置だったら
			else if (m_Object.ToZ < z && z <= m_Object.FadeToZ)
			{
				m_Object.Vertex[i].a = (unsigned char)(255.0f / (m_Object.FadeToZ - m_Object.ToZ) * (z - m_Object.ToZ));
			}
			//通常描画する位置なら
			else if (m_Object.FadeToZ <= z && z <= m_Object.FadeFromZ)
			{
				m_Object.Vertex[i].a = 255;
			}
			//(近づいてる場合)フェードアウトする位置だったら
			else if (m_Object.FadeFromZ <= z && z < m_Object.FromZ)
			{
				m_Object.Vertex[i].a = (unsigned char)(255.0f / (m_Object.FromZ - m_Object.FadeFromZ) * (m_Object.FromZ - z));
			}
			//描画する範囲より近かったら透過0
			else if (m_Object.FromZ < z)
			{
				m_Object.Vertex[i].a = 0;
			}
		}
	}
}

//****************************************************
//FUNCTION:
void CBackground3d::drawV()
{
	CNode::drawV();

	CHECK_RESULT(DxLib::DrawPolygon3D(m_Object.Vertex, 2, m_Object.Img, TRUE));
}