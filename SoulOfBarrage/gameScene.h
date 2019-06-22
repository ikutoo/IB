#pragma once
#include <vector>
#include "scene.h"

class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();

	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

private:
	void __drawUI();
	void __drawBarrage();
	void __drawPlayer();
	void __loadResource();

	int m_Counter = 0;
};