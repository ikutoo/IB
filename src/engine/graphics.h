#pragma once
#include <DXLib/DxLib.h>
#include "node.h"
#include "math.h"

namespace DxEngine
{
	class CBox2D : public CNode
	{
	public:
		CBox2D(recti vRect, int vColor = 0, bool vFill = true) : m_Rect(vRect), m_Color(vColor), m_Fill(vFill) {}

		virtual	void drawV() override;

	private:
		recti	m_Rect = {};
		int		m_Color = 0;
		bool	m_Fill = true;
	};

	class CLine2D : public CNode
	{
	public:
		CLine2D(vec2i vPointA, vec2i vPointB, int vColor = 0) : m_PointA(vPointA), m_PointB(vPointB), m_Color(vColor) {}

		virtual	void drawV() override;

	private:
		vec2i	m_PointA = {}, m_PointB = {};
		int		m_Color = 0;
	};

	class CBillboard3D : public CNode
	{
	public:
		CBillboard3D(VECTOR vPos, float vSize, float vAngle, const std::string& vImageFile);
		~CBillboard3D();

		virtual void drawV() override;

		void setAngle(float vAngle) { m_Angle = vAngle; }

	private:
		VECTOR	m_Position = {};
		float	m_Size = {};
		float	m_Angle = {};

		int		m_ImageHandle = -1;
		std::string	m_ImageFile = {};
	};

	class CPlane : public CNode
	{
	public:
		CPlane(FLOAT3 vPos, FLOAT3 vNormal, FLOAT2 vSize, float vAngle, const std::string& vImageFile, COLOR_U8 vColor = { 255, 255, 255, 255 });
		~CPlane();

		virtual void drawV() override;

		void setAngle(float vAngle) { m_Angle = vAngle; }
		float getAngle() const { return m_Angle; }

		void setColor(COLOR_U8 vColor) { m_Color = vColor; }
		COLOR_U8 getColor() const { return m_Color; }

	private:
		VERTEX_3D m_Vertices[6] = {};

		COLOR_U8 m_Color = {};
		FLOAT3 m_Position = {};
		FLOAT3 m_Normal = {};
		FLOAT2 m_Size = {};
		float  m_Angle = {};

		int			m_ImageHandle = -1;
		std::string	m_ImageFile = {};
	};
}