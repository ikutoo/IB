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

		void pause() { _IsPaused = true; }
		void resume() { _IsPaused = false; }

		void setPosition(const vec2f& vPos) { _Position = vPos; }
		void setPosition(float vPosX, float vPosY) { _Position.x = vPosX; _Position.y = vPosY; }
		void setLocalZ(float vLocalZ) { _LocalZ = vLocalZ; }

		void setRotation(float vRotation) { _Rotation = vRotation; }

		void setScale(const vec2f& vScale) { _Scale = vScale; }
		void setScale(float vScaleX, float vScaleY) { _Scale.x = vScaleX; _Scale.y = vScaleY; }

		void setBrightness(const vec3i& vBrightnessColor) { _BrightnessColor = vBrightnessColor; }

		void setName(const std::string& vName) { m_Name = vName; }

		CNode* findChild(const std::string& vName);

		const vec2f& getPosition() const { return _Position; }
		float getLocalZ() const { return _LocalZ; }
		const std::string& getName() const { return m_Name; }

		void addChild(CNode* vNode, float vLocalZ = 0.0f) { _ASSERT(vNode); vNode->setLocalZ(vLocalZ); _Childs.emplace_back(vNode); }
		void removeChild(CNode* vNode, bool vDestroyChild = true);
		void removeAllChilds(bool vDestroyChilds = true);

		uint32_t getNumChilds() const { return _Childs.size(); }

		uint32_t getCounter() const { return _Counter; }

	protected:
		vec2f _Position = { 0.0, 0.0 };
		vec2f _Scale = { 1.0, 1.0 };
		float _Rotation = 0.0;

		std::string m_Name = "";

		vec3i _BrightnessColor = { 255, 255, 255 };
		float _LocalZ = 0.0;

		std::list<CNode*> _Childs;

		uint32_t _Counter = 0;

		bool _IsPaused = false;
	};
}