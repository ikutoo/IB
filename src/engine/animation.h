#pragma once
#include <string>
#include <vector>
#include "math.h"

namespace DxEngine
{
	struct SAnimation
	{
		std::string ImageFile = "";
		recti Rect = {};

		int TotalFrames = 0;
		int CurrentFrame = 0;
		int LoopBeginFrame = 0;
		int LoopEndFrame = 0;

		bool IsLoop = true;
		bool IsFirstPassDone = false;

		std::vector<std::pair<int, recti>> KeyFrames;

		inline void reset() { CurrentFrame = 0; IsFirstPassDone = false; }
		inline recti forward() { update(); return Rect; }

		inline void update()
		{
			if (CurrentFrame >= TotalFrames) IsFirstPassDone = true;

			if (!IsLoop && IsFirstPassDone)
			{
				Rect = KeyFrames.back().second;
			}
			else if (IsLoop && IsFirstPassDone)
			{
				CurrentFrame %= TotalFrames;
				if (CurrentFrame < LoopBeginFrame) CurrentFrame = LoopBeginFrame;
				else if (CurrentFrame >= LoopEndFrame) CurrentFrame = LoopBeginFrame;
			}

			for (auto KeyFrame : KeyFrames)
			{
				if (CurrentFrame == KeyFrame.first) { Rect = KeyFrame.second; }
			}

			CurrentFrame++;
		}
	};
}