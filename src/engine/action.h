#pragma once
#include <functional>
#include "node.h"

namespace DxEngine
{
	namespace interpolator
	{
		inline float linear(float t) { return t; }
		inline float cubic(float t) { return (2 * (1 - t) - 3) * (1 - t) * (1 - t) + 1; }
	}

	class CAction
	{
	public:
		using TInterpFunc = std::function<float(float)>;

		virtual void updateV() = 0;

	protected:
		CNode* _pTarget = nullptr;

		bool _IsDone = false;

		friend class CActionManager;
	};

	class CMoveTo : public CAction
	{
	public:
		CMoveTo(CNode* vTarget, vec2f vFrom, vec2f vTo, float vTimeInMS, float vDelayTime = 0.0f, TInterpFunc vInterpFunc = interpolator::cubic);

		void updateV() override;

	private:

		vec2f m_VecFrom = {};
		vec2f m_VecTo = {};

		float m_TimeInMS = 0.0f;
		float m_DelayTime = 0.0f;

		int m_TotalFrameCount = 0;
		int m_CurrentFrame = 0;

		TInterpFunc m_InterpFunc;
	};
}