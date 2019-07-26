#include "stdafx.h"
#include "background3d.h"
#include "engine/common.h"
#include "engine/resourceManager.h"
#include "common.h"

using namespace DxEngine;

const VtPm_t VtPm[6] = { {-1,1,0,0},{1,1,1,0},{-1,-1,0,1},{1,-1,1,1},{-1,-1,0,1},{1,1,1,0} };

//****************************************************
//FUNCTION:
CBackground3d::CBackground3d()
{
	int ImgHandle;
	ObjectNum = 0;
	ImgHandle = CResourceManager::getInstance()->loadImage("tex.png");
	__initObject(&Object[0], ImgHandle, 512, 0, 0, 256, 128, 250, 50, 2, 1000, 400, -200, -400, GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2 - 90, OBCHILD_MAX);
	__initObject(&Object[1], ImgHandle, 512, 60, 270, 405, 512, 180, 125, 0, 1000, 400, -200, -400, 670, 275, 6);
	ImgHandle = CResourceManager::getInstance()->loadImage("kabe.png");
	__initObject(&Object[2], ImgHandle, 512, 0, 0, 390, 512, 73, 90, 1, 1000, 400, -200, -400, 370, 240, OBCHILD_MAX);
}

//****************************************************
//FUNCTION:
void CBackground3d::updateV(double vDeltaTime)
{
	CNode::updateV(vDeltaTime);

	__clacObject();
	__sortObject();
}

//****************************************************
//FUNCTION:
void CBackground3d::drawV()
{
	CNode::drawV();

	SetDrawMode(DX_DRAWMODE_BILINEAR);//ポリゴンが荒く見えないような描画の仕方「バイリニア法」
	for (int t = 0; t < ObjectNum; t++) {
		for (int s = 0; s < Object[t].ObchindMax; s++) {
			DrawPolygon3D(Object[t].ObChild[s].Vertex, 2, Object[t].Img, TRUE);
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);//描画の仕方を元に戻す
}

//****************************************************
//FUNCTION:
void CBackground3d::__initObject(Object_t *Ob, int ImgHandle, int ImgSize, int ImgX1, int ImgY1, int ImgX2, int ImgY2, float LargeX, float LargeY,
	int Type, float FromZ, float FadeFromZ, float FadeToZ, float ToZ, float GraphX, float GraphY, int ObchildMax) {
	int i, s;

	if (ObjectNum >= OBJECT_NUM_MAX - 1) {
		printfDx("オブジェクト登録オーバー\n");
		return;
	}
	ObjectNum++;//オブジェクトの登録数加算

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
	for (s = 0; s < Ob->ObchindMax; s++) {
		Ob->ObChild[s].x = GraphX;
		Ob->ObChild[s].y = GraphY;
		Ob->ObChild[s].z = Ob->ToZ - Ob->Zhaba + Ob->Zhaba * s;;
		for (i = 0; i < 6; i++) {
			Ob->ObChild[s].Vertex[i].r = Ob->ObChild[s].Vertex[i].g = Ob->ObChild[s].Vertex[i].b = Ob->ObChild[s].Vertex[i].a = 255;
			Ob->ObChild[s].Vertex[i].u = ou1 + ou2 * VtPm[i].u;
			Ob->ObChild[s].Vertex[i].v = ov1 + ov2 * VtPm[i].v;
		}
	}
}

//***********************************************************************************************
//FUNCTION:
void CBackground3d::__clacObject() {
	int t, s, i;
	for (t = 0; t < ObjectNum; t++) {
		for (s = 0; s < Object[t].ObchindMax; s++) {
			Object[t].ObChild[s].z -= 3;
			for (i = 0; i < 6; i++) {
				switch (Object[t].Type) {
				case 0://画面に平行
					Object[t].ObChild[s].Vertex[i].pos.x = Object[t].ObChild[s].x + Object[t].LargeX * VtPm[i].x;
					Object[t].ObChild[s].Vertex[i].pos.y = Object[t].ObChild[s].y + Object[t].LargeY * VtPm[i].y;
					Object[t].ObChild[s].Vertex[i].pos.z = Object[t].ObChild[s].z;
					break;
				case 1://画面に垂直(壁)
					Object[t].ObChild[s].Vertex[i].pos.x = Object[t].ObChild[s].x;
					Object[t].ObChild[s].Vertex[i].pos.y = Object[t].ObChild[s].y + Object[t].LargeY * VtPm[i].y;
					Object[t].ObChild[s].Vertex[i].pos.z = Object[t].ObChild[s].z + Object[t].Zhaba / 2 * VtPm[i].x;
					break;
				case 2://画面に垂直(床)
					Object[t].ObChild[s].Vertex[i].pos.x = Object[t].ObChild[s].x + Object[t].LargeX * VtPm[i].x;
					Object[t].ObChild[s].Vertex[i].pos.y = Object[t].ObChild[s].y;
					Object[t].ObChild[s].Vertex[i].pos.z = Object[t].ObChild[s].z + Object[t].Zhaba / 2 * VtPm[i].y;
					break;
				}
			}
		}

		if (Object[t].FromZ - Object[t].FadeFromZ <= 0) {
			printfDx("Object[%d].Fromの設定がおかしい\n", t);
		}
		else if (Object[t].FadeToZ - Object[t].ToZ <= 0) {
			printfDx("Object[%d].Toの設定がおかしい\n", t);
		}
		else {
			for (s = 0; s < Object[t].ObchindMax; s++) {
				for (i = 0; i < 6; i++) {
					float z = Object[t].ObChild[s].Vertex[i].pos.z;
					//位置が描画する範囲より遠かったら透過0
					if (z < Object[t].ToZ) {
						Object[t].ObChild[s].Vertex[i].a = 0;
					}
					//(近づいている場合)フェードインする位置だったら
					else if (Object[t].ToZ < z && z <= Object[t].FadeToZ) {
						Object[t].ObChild[s].Vertex[i].a = (unsigned char)(255.0f / (Object[t].FadeToZ - Object[t].ToZ) * (z - Object[t].ToZ));
					}
					//通常描画する位置なら
					else if (Object[t].FadeToZ <= z && z <= Object[t].FadeFromZ) {
						Object[t].ObChild[s].Vertex[i].a = 255;
					}
					//(近づいてる場合)フェードアウトする位置だったら
					else if (Object[t].FadeFromZ <= z && z < Object[t].FromZ) {
						Object[t].ObChild[s].Vertex[i].a = (unsigned char)(255.0f / (Object[t].FromZ - Object[t].FadeFromZ) * (Object[t].FromZ - z));
					}
					//描画する範囲より近かったら透過0
					else if (Object[t].FromZ < z) {
						Object[t].ObChild[s].Vertex[i].a = 0;
					}
				}
				//近づいて見えなくなったら
				if (Object[t].ObChild[s].z < Object[t].ToZ - Object[t].Zhaba*0.5f) {
					//一番向こう側へ
					float sub = (Object[t].ToZ - Object[t].Zhaba*0.5f) - Object[t].ObChild[s].z;
					Object[t].ObChild[s].z = Object[t].FromZ + Object[t].Zhaba*0.5f - sub;
				}
				//遠ざかって見えなくなったら
				else if (Object[t].ObChild[s].z > Object[t].FromZ + Object[t].Zhaba*0.5f) {
					//一番こちら側へ
					float sub = Object[t].ObChild[s].z - (Object[t].FromZ + Object[t].Zhaba*0.5f);
					Object[t].ObChild[s].z = Object[t].ToZ - Object[t].Zhaba*0.5f + sub;
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
void CBackground3d::__sortObject() {
	int i, j, t;
	for (t = 0; t < ObjectNum; t++) {
		for (i = 0; i < Object[t].ObchindMax; i++) {
			for (j = i + 1; j < Object[t].ObchindMax; j++) {
				if (Object[t].ObChild[i].z < Object[t].ObChild[j].z) {
					__swapObChild(&Object[t].ObChild[i], &Object[t].ObChild[j]);
				}
			}
		}
	}
}