#pragma once
#include <list>
#include "math.h"

namespace DxEngine
{
	class CNode
	{
	public:
		CNode() = default;
		virtual ~CNode() = default;

		virtual void updateV(double vDeltaTime);
		virtual void drawV();

		void setPosition(vec2f vPos) { _Position = vPos; }
		void setPosition(float vPosX, float vPosY) { _Position.x = vPosX; _Position.y = vPosY; }
		void setLocalZ(float vLocalZ) { _LocalZ = vLocalZ; }

		void setRotation(float vRotation) { _Rotation = vRotation; }

		void setScale(float vScaleX, float vScaleY) { _Scale.x = vScaleX; _Scale.y = vScaleY; }

		void setBrightness(vec3i vBrightnessColor) { _BrightnessColor = vBrightnessColor; }

		const vec2f& getPosition() const { return _Position; }
		float getLocalZ() const { return _LocalZ; }

		void addChild(CNode* vNode, float vLocalZ = 0.0f) { _ASSERT(vNode); vNode->setLocalZ(vLocalZ); _Childs.emplace_back(vNode); }
		void removeChild(CNode* vNode, bool vDestroyChild = true);
		void removeAllChilds(bool vDestroyChilds = true);

		uint32_t getNumChilds() const { return _Childs.size(); }

		uint32_t getCounter() const { return _Counter; }

	protected:
		vec2f _Position = { 0.0, 0.0 };
		vec2f _Scale = { 1.0, 1.0 };
		float _Rotation = 0.0;

		vec3i _BrightnessColor = { 255, 255, 255 };
		float _LocalZ = 0.0;

		std::list<CNode*> _Childs;

		uint32_t _Counter = 0;
	};
}