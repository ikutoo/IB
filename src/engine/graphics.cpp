#include "graphics.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

typedef struct
{
	float x, y;
	float u, v;
} VtPm_t;

const VtPm_t VtPm[6] = { {-1,1,0,0},{1,1,1,0},{-1,-1,0,1},{1,-1,1,1},{-1,-1,0,1},{1,1,1,0} };

//*********************************************************************
//FUNCTION:
void DxEngine::CBox2D::drawV()
{
	CNode::drawV();
	CHECK_RESULT(DxLib::DrawBox(m_Rect.x, m_Rect.y, m_Rect.x + m_Rect.w, m_Rect.y + m_Rect.h, m_Color, m_Fill));
}

//*********************************************************************
//FUNCTION:
void DxEngine::CLine2D::drawV()
{
	CNode::drawV();
	CHECK_RESULT(DxLib::DrawLine(m_PointA.x, m_PointA.y, m_PointB.x, m_PointB.y, m_Color));
}

//*********************************************************************
//FUNCTION:
DxEngine::CBillboard3D::CBillboard3D(VECTOR vPos, float vSize, float vAngle, const std::string& vImageFile) : m_Position(vPos), m_Size(vSize), m_Angle(vAngle), m_ImageFile(vImageFile)
{
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERT(m_ImageHandle != -1);
}

//*********************************************************************
//FUNCTION:
DxEngine::CBillboard3D::~CBillboard3D()
{
	CResourceManager::getInstance()->deleteImage(m_ImageFile);
}

//*********************************************************************
//FUNCTION:
void DxEngine::CBillboard3D::drawV()
{
	CNode::drawV();
	CHECK_RESULT(DxLib::DrawBillboard3D(m_Position, 0.5, 0.5, m_Size, m_Angle, m_ImageHandle, TRUE));
}

//*********************************************************************
//FUNCTION:
DxEngine::CPlane::CPlane(FLOAT3 vPos, FLOAT3 vNormal, FLOAT2 vSize, float vAngle, const std::string& vImageFile, COLOR_U8 vColor)
	: m_Position(vPos), m_Normal(vNormal), m_Size(vSize), m_Angle(vAngle), m_ImageFile(vImageFile), m_Color(vColor)
{
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERT(m_ImageHandle != -1);
}

//*********************************************************************
//FUNCTION:
DxEngine::CPlane::~CPlane()
{
	CResourceManager::getInstance()->deleteImage(m_ImageFile);
}

//*********************************************************************
//FUNCTION:
void DxEngine::CPlane::drawV()
{
	CNode::drawV();

	auto Mat = MGetRotAxis(VGet(0, 0, -1), m_Angle);
	Mat = MMult(Mat, MGetRotVec2(VGet(0, 0, -1), m_Normal));
	Mat = MMult(Mat, MGetTranslate(m_Position));

	for (int i = 0; i < 6; i++)
	{
		m_Vertices[i].r = m_Color.r;
		m_Vertices[i].g = m_Color.g;
		m_Vertices[i].b = m_Color.b;
		m_Vertices[i].a = m_Color.a;
		m_Vertices[i].u = VtPm[i].u;
		m_Vertices[i].v = VtPm[i].v;
		m_Vertices[i].pos = VTransform(VGet(m_Size.u / 2 * VtPm[i].x, m_Size.v / 2 * VtPm[i].y, 0), Mat);
	}

	CHECK_RESULT(DxLib::DrawPolygon3D(m_Vertices, 2, m_ImageHandle, TRUE));
}