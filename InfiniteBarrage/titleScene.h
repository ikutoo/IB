#pragma once
#include <vector>
#include "common.h"
#include "scene.h"

class CTitleScene : public CScene
{
public:
	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

private:
	SLabel m_TitleLabel;
	SLabel m_FlagLabel;
	std::vector<SLabel> m_MenuLabels;

	int m_SelectedLabelIndex = 0;

	void __drawUI();
	void __handleInput();
};