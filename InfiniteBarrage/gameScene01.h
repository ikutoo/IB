#pragma once
#include "scene.h"

class CGameScene01 : public CScene
{
public:
	CGameScene01();
	~CGameScene01();

	virtual void updateV(double vDeltaTime) override;
};