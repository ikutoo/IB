#pragma once
#include <functional>
#include <vector>
#include "node.h"

namespace DxEngine
{
	namespace interpolator
	{
		inline float linear(float t) { return t; }
		inline float cubic(float t) { return (2 * (1 - t) - 3) * (1 - t) * (1 - t) + 1; }
		inline float sine(float t) { return 0.5*sin((t - 0.5)*PI) + 0.5; }
	}

	class CAction
	{
	public:
		using TInterpFunc = std::function<float(float)>;

		virtual void updateV() = 0;

		bool isDone() const { return _IsDone; }

	protected:
		CNode* _pTarget = nullptr;

		bool _IsDone = false;

		friend class CActionManager;
	};

	class CMoveTo : public CAction
	{
	public:
		CMoveTo(CNode* vTarget, vec2f vFrom, vec2f vTo, float vTimeInMS, float vDelayTimeInMS = 0.0f, TInterpFunc vInterpFunc = interpolator::cubic);

		void updateV() override;

	private:

		vec2f m_VecFrom = {};
		vec2f m_VecTo = {};

		float m_TimeInMS = 0.0f;
		float m_DelayTime = 0.0f;

		int m_TotalFrameCount = 0;
		int m_DelayFrameCount = 0;
		int m_CurrentFrame = 0;

		TInterpFunc m_InterpFunc;
	};

	class CActionSequence : public CAction
	{
	public:
		CActionSequence(CNode* vTarget, const std::vector<CAction*>& vActionSequence);
		~CActionSequence();

		void updateV() override;

	private:
		std::vector<CAction*> m_ActionSequence;
		int m_CurrentActionIndex = 0;
	};
}