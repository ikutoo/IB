#pragma once
#include <vector>
#include "scene.h"
#include "label.h"

class CTitleScene : public  DxEngine::CScene
{
public:
	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

private:
	DxEngine::CImageLabel* m_pFlagLabel = nullptr;
	std::vector<DxEngine::CImageLabel*> m_MenuLabels;

	int m_SelectedLabelIndex = 0;
};