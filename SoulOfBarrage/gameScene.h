#pragma once
#include "scene.h"

class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();

	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;

private:
	void __drawUI();
	void __drawBarrage();
	void __drawPlayer();
	void __loadResource();
};