#pragma once
#include <functional>
#include "node.h"

namespace DxEngine
{
	namespace interpolator
	{
		inline float linear(float t) { return t; }
		inline float cubic(float t) { return (2 * t - 3) * t * t + 1; }
	}

	class CAction
	{
	public:
		using TInterpFunc = std::function<float(float)>;

		virtual void updateV() = 0;
	};

	class CMoveTo : public CAction
	{
	public:
		CMoveTo(CNode* vTarget, vec2f vFrom, vec2f vTo, float vTimeInMS, TInterpFunc vInterpFunc = interpolator::linear);

		void updateV() override;

	private:
		CNode* m_pTarget = nullptr;

		vec2f m_VecFrom = {};
		vec2f m_VecTo = {};

		float m_TimeInMS = 0.0f;

		int m_TotalFrameCount = 0;
		int m_CurrentFrame = 0;

		TInterpFunc m_InterpFunc;
	};
}