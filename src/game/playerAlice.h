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

	void __updateAnimation();
	void __updateBarrage();
};