#pragma once
#include "engine/sprite.h"

#define OBCHILD_MAX 11
#define OBJECT_NUM_MAX 10

typedef struct {
	float x, y;
	float u, v;
}VtPm_t;

//一つのテクスチャーについての構造体
typedef struct {
	float x, y, z;//中心点
	VERTEX_3D Vertex[6];        //描画用頂点6個
} ObChild_t;

typedef struct {
	int Type;    // 0:画面に平行、1:画面に垂直
	int Img;    //画像
	int ImgSize;
	int ImgX1, ImgX2, ImgY1, ImgY2;
	float LargeX, LargeY;//縦横の大きさ(Typeが1の時はLargeXがLargeZの役割をする)
	float Zhaba;
	float FromZ, ToZ;    //どこからどこまで奥行きを設定するか
	float FadeFromZ, FadeToZ;    //どこからどこまでフェードを設定するか(消える瞬間フェードアウト、現れる瞬間フェードインする)
	int ObchindMax;
	ObChild_t ObChild[OBCHILD_MAX];
} Object_t;

class CBackground3d : public DxEngine::CNode
{
public:
	CBackground3d();
	~CBackground3d() {}

	void updateV(double vDeltaTime) override;
	void drawV() override;

private:
	Object_t m_Objects[OBJECT_NUM_MAX];
	int m_ObjectNum = 0;

	void __initObject(Object_t *Ob, int ImgHandle, int ImgSize, int ImgX1, int ImgY1, int ImgX2, int ImgY2, float LargeX, float LargeY,
		int Type, float FromZ, float FadeFromZ, float FadeToZ, float ToZ, float GraphX, float GraphY, int ObchildMax);
	void __clacObject();
	void __sortObject();
};