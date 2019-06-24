#pragma once
#include <vector>
#include "scene.h"

class CLevelScene : public CScene
{
public:
	bool initV() override;
	void updateV(double vDeltaTime) override;
	void destroyV() override;

private:
	SImageLabel m_FlagLabel;
	std::vector<SImageLabel> m_MenuLabels;
	int m_SelectedLabelIndex = 0;

	void __drawUI();
	void __handleInput();
};