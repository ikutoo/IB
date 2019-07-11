#pragma once
#include <map>
#include "node.h"

namespace DxEngine
{
	class CSprite : public CNode
	{
	public:
		CSprite(const std::string& vImageFile = "", const recti& vRect = {});
		virtual ~CSprite();

		void drawV() override;

		void setImageFile(const std::string& vImageFile, const recti& vRect = {});
		void setRect(const recti& vRect) { m_Rect = vRect; m_Size = { vRect.w, vRect.h }; }
		void setAnchor(vec2i vAnchor) { m_Anchor = vAnchor; }

		vec2i getSize() const;

		void flip() { m_IsFliped = !m_IsFliped; }
		void setFlip(bool vFlip) { m_IsFliped = vFlip; }

		void setImageRotation(float vRotation) { m_ImageRotation = vRotation; }

		void setPriorToChildsHint() { m_PriorToChilds = true; }

		void setRenderGraph(int vRenderGraph, bool vClearOnDraw = true) { m_RenderGraph = vRenderGraph; m_ClearRenderTargetOnDraw = vClearOnDraw; }

	private:
		int m_ImageHandle = -1;
		int m_RenderGraph = -1;
		std::string m_ImageFile = {};

		recti m_Rect = {};
		vec2i m_Size = {};
		vec2i m_Anchor = {};

		float m_ImageRotation = 0.0;

		bool m_IsFliped = false;
		bool m_PriorToChilds = false; //若为true, 则优先于childs进行绘制
		bool m_ClearRenderTargetOnDraw = true;
	};
}