#pragma once
#include "player.h"

class CPlayerAlice : public CPlayer
{
public:
	CPlayerAlice(const std::string& vConfigFile);
	~CPlayerAlice();

	virtual void updateV(double vDeltaTime) override;

private:
	std::vector<CSprite*> m_Dolls;

	SAnimation m_DollAnimation;

	float m_Theta = 0.0f;

	int m_CurrentShootMode = 0;
	std::vector<std::vector<vec2f>> m_InitialDollPosSet;

	void __calculateInitialDollPos();
	void __changeShootingMode();
	void __updateAnimation();
};