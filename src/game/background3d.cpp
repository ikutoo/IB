#include "stdafx.h"
#include "background3d.h"
#include "engine/common.h"
#include "engine/resourceManager.h"
#include "barrageManager.h"
#include "common.h"

using namespace DxEngine;

const VtPm_t VtPm[6] = { {-1,1,0,0},{1,1,1,0},{-1,-1,0,1},{1,-1,1,1},{-1,-1,0,1},{1,1,1,0} };

//****************************************************
//FUNCTION:
CBackground3d::CBackground3d()
{
	const float FromZ = 2000, FadeFromZ = 800, FadeToZ = 200, ToZ = 0;

	auto ImgHandle = CResourceManager::getInstance()->loadImage("stage0_bg_01.png");
	__initObject(&m_Objects[0], ImgHandle, 512, 10, 266, 246, 502, 256, 512, 2, FromZ, FadeFromZ, FadeToZ, ToZ, GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2 - 90, OBCHILD_MAX);

	__initObject(&m_Objects[1], ImgHandle, 512, 260, 0, 384, 128, 64, 64, 3, FromZ, FadeFromZ, FadeToZ, ToZ, GRAPH_SIZE_X - 850, GRAPH_SIZE_Y / 2, OBCHILD_MAX);
	__initObject(&m_Objects[2], ImgHandle, 512, 260, 0, 384, 128, 48, 48, 3, FromZ, FadeFromZ, FadeToZ, ToZ, GRAPH_SIZE_X - 850, GRAPH_SIZE_Y / 2 + 32, OBCHILD_MAX);
	__initObject(&m_Objects[3], ImgHandle, 512, 260, 0, 384, 128, 32, 32, 3, FromZ, FadeFromZ, FadeToZ, ToZ, GRAPH_SIZE_X - 850, GRAPH_SIZE_Y / 2 + 48, OBCHILD_MAX);

	__initObject(&m_Objects[4], ImgHandle, 512, 384, 0, 512, 128, 64, 64, 3, FromZ + 400, FadeFromZ, FadeToZ, ToZ, 850, GRAPH_SIZE_Y / 2, OBCHILD_MAX);
	__initObject(&m_Objects[5], ImgHandle, 512, 384, 0, 512, 128, 48, 48, 3, FromZ + 400, FadeFromZ, FadeToZ, ToZ, 850, GRAPH_SIZE_Y / 2 + 32, OBCHILD_MAX);
	__initObject(&m_Objects[6], ImgHandle, 512, 384, 0, 512, 128, 32, 32, 3, FromZ + 400, FadeFromZ, FadeToZ, ToZ, 850, GRAPH_SIZE_Y / 2 + 48, OBCHILD_MAX);
}

//*********************************************************************
//FUNCTION:
CBackground3d::~CBackground3d()
{
	CResourceManager::getInstance()->deleteImage("stage0_bg_01.png");
}

//****************************************************
//FUNCTION:
void CBackground3d::updateV(double vDeltaTime)
{
	CNode::updateV(vDeltaTime);

	if (_Counter < 560) m_Speed = 0.0;
	else m_Speed = 3.0;
}

//****************************************************
//FUNCTION:
void CBackground3d::drawV()
{
	CNode::drawV();

	static float a = 0.0;
	if (_Counter < 560)	a += 0.5;
	auto PlayerPos = CBarrageManager::getInstance()->getPlayerPosition();
	auto OffsetX = 0.02 + 0.05 * (2 * PlayerPos.x - GRAPH_SIZE_X) / GRAPH_SIZE_X;
	DxLib::SetCameraPositionAndTargetAndUpVec(VGet(GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2 + a, 0), VGet(GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2, 200), VGet(OffsetX, 1, 0));

	__clacObject();
	__sortObject();

	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for (int t = 0; t < m_ObjectNum; t++) {
		for (int s = 0; s < m_Objects[t].ObchindMax; s++) {
			DrawPolygon3D(m_Objects[t].ObChild[s].Vertex, 2, m_Objects[t].Img, TRUE);
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

//****************************************************
//FUNCTION:
void CBackground3d::__initObject(Object_t *Ob, int ImgHandle, int ImgSize, int ImgX1, int ImgY1, int ImgX2, int ImgY2, float LargeX, float LargeY,
	int Type, float FromZ, float FadeFromZ, float FadeToZ, float ToZ, float GraphX, float GraphY, int ObchildMax) {
	int i, s;

	if (m_ObjectNum >= OBJECT_NUM_MAX - 1) {
		printfDx("オブジェクト登録オーバー\n");
		return;
	}
	m_ObjectNum++;//オブジェクトの登録数加算

	Ob->Img = ImgHandle;//画像ハンドル
	Ob->ImgSize = ImgSize;//画像サイズ
	Ob->ImgX1 = ImgX1;
	Ob->ImgY1 = ImgY1;
	Ob->ImgX2 = ImgX2;
	Ob->ImgY2 = ImgY2;
	Ob->LargeX = LargeX;//とりあえず描画する大きさを適当に設定。縦・横比は素材の通りにする
	Ob->LargeY = LargeY;
	Ob->Type = Type;//タイプを垂直に
	Ob->FromZ = FromZ;//描画開始地点
	Ob->FadeFromZ = FadeFromZ;//描画フェードイン開始地点
	Ob->FadeToZ = FadeToZ;//描画フェードアウト開始地点
	Ob->ToZ = ToZ;//描画終了地点
	Ob->ObchindMax = OBCHILD_MAX;
	if (Ob->Type == 0) {
		Ob->ObchindMax = ObchildMax;
	}
	if (Ob->ObchindMax - 1 <= 0) {
		printfDx("表示数の設定が異常です\n");
		return;
	}
	//Zの幅計算
	Ob->Zhaba = (Ob->FromZ - Ob->ToZ) / (Ob->ObchindMax - 1);

	float ou1 = (float)Ob->ImgX1 / Ob->ImgSize, ou2 = (float)(Ob->ImgX2 - Ob->ImgX1) / Ob->ImgSize;
	float ov1 = (float)Ob->ImgY1 / Ob->ImgSize, ov2 = (float)(Ob->ImgY2 - Ob->ImgY1) / Ob->ImgSize;
	for (s = 0; s < Ob->ObchindMax; s++)
	{
		Ob->ObChild[s].Pos = VGet(GraphX, GraphY, Ob->ToZ - Ob->Zhaba + Ob->Zhaba * s);
		for (i = 0; i < 6; i++)
		{
			Ob->ObChild[s].Vertex[i].r = Ob->ObChild[s].Vertex[i].g = Ob->ObChild[s].Vertex[i].b = Ob->ObChild[s].Vertex[i].a = 255;
			Ob->ObChild[s].Vertex[i].u = ou1 + ou2 * VtPm[i].u;
			Ob->ObChild[s].Vertex[i].v = ov1 + ov2 * VtPm[i].v;
		}
	}
}

//***********************************************************************************************
//FUNCTION:
void CBackground3d::__clacObject()
{
	for (int t = 0; t < m_ObjectNum; t++) {
		for (int s = 0; s < m_Objects[t].ObchindMax; s++) {
			m_Objects[t].ObChild[s].Pos.z -= m_Speed;
			VECTOR CameraPos = GetCameraPosition();
			VECTOR View = VSub(CameraPos, m_Objects[t].ObChild[s].Pos);
			MATRIX Mat = MGetTranslate(VSub(VGet(0, 0, 0), m_Objects[t].ObChild[s].Pos));
			Mat = MMult(Mat, MGetRotVec2(VGet(0, 0, -1), View));
			Mat = MMult(Mat, MGetTranslate(m_Objects[t].ObChild[s].Pos));
			for (int i = 0; i < 6; i++) {
				switch (m_Objects[t].Type) {
				case 0://与z轴垂直
					m_Objects[t].ObChild[s].Vertex[i].pos = VAdd(m_Objects[t].ObChild[s].Pos, VGet(m_Objects[t].LargeX * VtPm[i].x, m_Objects[t].LargeY * VtPm[i].y, 0));
					break;
				case 1://与x轴垂直
					m_Objects[t].ObChild[s].Vertex[i].pos = VAdd(m_Objects[t].ObChild[s].Pos, VGet(0, m_Objects[t].LargeY * VtPm[i].y, m_Objects[t].Zhaba / 2 * VtPm[i].x));
					break;
				case 2://与y轴垂直
					m_Objects[t].ObChild[s].Vertex[i].pos = VAdd(m_Objects[t].ObChild[s].Pos, VGet(m_Objects[t].LargeX * VtPm[i].x, 0, m_Objects[t].Zhaba / 2 * VtPm[i].y));
					break;
				case 3: //始终朝向摄像机
					m_Objects[t].ObChild[s].Vertex[i].pos = VAdd(m_Objects[t].ObChild[s].Pos, VGet(m_Objects[t].LargeX * VtPm[i].x, m_Objects[t].LargeY * VtPm[i].y, 0));
					m_Objects[t].ObChild[s].Vertex[i].pos = VTransform(m_Objects[t].ObChild[s].Vertex[i].pos, Mat);
					break;
				}
			}
		}

		if (m_Objects[t].FromZ - m_Objects[t].FadeFromZ <= 0) {
			printfDx("Object[%d].Fromの設定がおかしい\n", t);
		}
		else if (m_Objects[t].FadeToZ - m_Objects[t].ToZ <= 0) {
			printfDx("Object[%d].Toの設定がおかしい\n", t);
		}
		else {
			for (int s = 0; s < m_Objects[t].ObchindMax; s++) {
				for (int i = 0; i < 6; i++) {
					float z = m_Objects[t].ObChild[s].Vertex[i].pos.z;
					//位置が描画する範囲より遠かったら透過0
					if (z < m_Objects[t].ToZ) {
						m_Objects[t].ObChild[s].Vertex[i].a = 0;
					}
					//(近づいている場合)フェードインする位置だったら
					else if (m_Objects[t].ToZ < z && z <= m_Objects[t].FadeToZ) {
						m_Objects[t].ObChild[s].Vertex[i].a = (unsigned char)(255.0f / (m_Objects[t].FadeToZ - m_Objects[t].ToZ) * (z - m_Objects[t].ToZ));
					}
					//通常描画する位置なら
					else if (m_Objects[t].FadeToZ <= z && z <= m_Objects[t].FadeFromZ) {
						m_Objects[t].ObChild[s].Vertex[i].a = 255;
					}
					//(近づいてる場合)フェードアウトする位置だったら
					else if (m_Objects[t].FadeFromZ <= z && z < m_Objects[t].FromZ) {
						m_Objects[t].ObChild[s].Vertex[i].a = (unsigned char)(255.0f / (m_Objects[t].FromZ - m_Objects[t].FadeFromZ) * (m_Objects[t].FromZ - z));
					}
					//描画する範囲より近かったら透過0
					else if (m_Objects[t].FromZ < z) {
						m_Objects[t].ObChild[s].Vertex[i].a = 0;
					}
				}
				//近づいて見えなくなったら
				if (m_Objects[t].ObChild[s].Pos.z < m_Objects[t].ToZ - m_Objects[t].Zhaba*0.5f) {
					//一番向こう側へ
					float sub = (m_Objects[t].ToZ - m_Objects[t].Zhaba*0.5f) - m_Objects[t].ObChild[s].Pos.z;
					m_Objects[t].ObChild[s].Pos.z = m_Objects[t].FromZ + m_Objects[t].Zhaba*0.5f - sub;
				}
				//遠ざかって見えなくなったら
				else if (m_Objects[t].ObChild[s].Pos.z > m_Objects[t].FromZ + m_Objects[t].Zhaba*0.5f) {
					//一番こちら側へ
					float sub = m_Objects[t].ObChild[s].Pos.z - (m_Objects[t].FromZ + m_Objects[t].Zhaba*0.5f);
					m_Objects[t].ObChild[s].Pos.z = m_Objects[t].ToZ - m_Objects[t].Zhaba*0.5f + sub;
				}
			}
		}
	}
}

//***********************************************************************************************
//FUNCTION:
void __swapObChild(ObChild_t *Ob1, ObChild_t *Ob2) {
	ObChild_t t = *Ob1;
	*Ob1 = *Ob2;
	*Ob2 = t;
}

//***********************************************************************************************
//FUNCTION:
void CBackground3d::__sortObject()
{
	for (int t = 0; t < m_ObjectNum; t++)
	{
		for (int i = 0; i < m_Objects[t].ObchindMax; i++)
		{
			for (int j = i + 1; j < m_Objects[t].ObchindMax; j++)
			{
				if (m_Objects[t].ObChild[i].Pos.z < m_Objects[t].ObChild[j].Pos.z)
					__swapObChild(&m_Objects[t].ObChild[i], &m_Objects[t].ObChild[j]);
			}
		}
	}
}