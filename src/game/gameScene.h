#pragma once
#include <vector>
#include "engine/scene.h"
#include "engine/sprite.h"
#include "engine/label.h"

class CGameScene : public  DxEngine::CScene
{
public:
	CGameScene() = default;
	~CGameScene() = default;

	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

private:
	bool __initUI();
	void __updateBarrage();

	DxEngine::CSprite* m_pChSprite = nullptr;
	DxEngine::CSprite* m_pBgSprite = nullptr;

	DxEngine::CTextLabel* m_pScoreDesc = nullptr;
	DxEngine::CTextLabel* m_pPlayerDesc = nullptr;
	DxEngine::CTextLabel* m_pBombDesc = nullptr;
	DxEngine::CTextLabel* m_pPowerDesc = nullptr;
	DxEngine::CTextLabel* m_pScoreValue = nullptr;
	DxEngine::CTextLabel* m_pPlayerValue = nullptr;
	DxEngine::CTextLabel* m_pBombValue = nullptr;
	DxEngine::CTextLabel* m_pPowerValue = nullptr;

	int m_Counter = 0;
};