#pragma once
#include "engine/sprite.h"

#define OBCHILD_MAX 11
#define OBJECT_NUM_MAX 10

typedef struct {
	float x, y;
	float u, v;
}VtPm_t;

//һ�ĤΥƥ�������`�ˤĤ��ƤΘ�����
typedef struct {
	float x, y, z;//���ĵ�
	VERTEX_3D Vertex[6];        //�軭��픵�6��
} ObChild_t;

typedef struct {
	int Type;    // 0:�����ƽ�С�1:����˴�ֱ
	int Img;    //����
	int ImgSize;
	int ImgX1, ImgX2, ImgY1, ImgY2;
	float LargeX, LargeY;//�k��δ󤭤�(Type��1�Εr��LargeX��LargeZ���۸�򤹤�)
	float Zhaba;
	float FromZ, ToZ;    //�ɤ�����ɤ��ޤǰ��Ф����O�����뤫
	float FadeFromZ, FadeToZ;    //�ɤ�����ɤ��ޤǥե��`�ɤ��O�����뤫(������˲�g�ե��`�ɥ����ȡ��F���˲�g�ե��`�ɥ��󤹤�)
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