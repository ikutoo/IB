#pragma once
#include "scene.h"

class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();

	virtual void updateV(double vDeltaTime) override;
};