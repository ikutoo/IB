#pragma once

namespace DxEngine
{
	class CScene
	{
	public:
		CScene();
		virtual ~CScene();

		virtual bool initV() { return true; }
		virtual void updateV(double vDeltaTime) {}
		virtual void destroyV() {}
	};
}