#pragma once
#include <vector>
#include "engine/scene.h"

class CBarrageLayer
{

};

class CGameScene : public  DxEngine::CScene
{
public:
	CGameScene();
	~CGameScene();

	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;
	virtual void drawV() override;

private:
	void __updateBarrage();

	int m_Counter = 0;
};