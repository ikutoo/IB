#pragma once
#include <vector>
#include "common.h"

class CTitleScene
{
public:
	CTitleScene();
	~CTitleScene();

	bool init();
	void update();

private:
	SLabel m_TitleLabel;
	SLabel m_FlagLabel;
	std::vector<SLabel> m_MenuLabels;

	int m_SelectedLabelIndex = 0;

	void __drawUI();
};