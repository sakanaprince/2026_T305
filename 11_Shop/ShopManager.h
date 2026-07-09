#pragma once
#include "BuyButton.h"
#include "../DxPlus/DxPlus.h"

#include "BuyTutorial.h"
#include "BuyRepair.h"
#include "BuyHolySushi.h"
#include "BuyTrap.h"
#include "BuyMap.h"
class GameContext;

class ShopManager
{
public:
	ShopManager() = default;
	void Init(GameContext* gC);
	void Update(float deltaTime);
	void Draw()const;

	bool IsShopOpen(){ return isShopOpen; }
	void SwitchShopOpen()
	{ 
		isShopOpen = !isShopOpen; 
		for (auto& b : btnCollection)
		{
			b->SetEffectDeActive();
		}
	}
	const bool GetPrevFrameMouseDown()const  { return prevFrameMouseDown; }

	GameContext* GetGameContext() { return pGameContext; }
	const DxPlus::Vec2Int& GetMousePos() const{ return mousePos; }

private:
	GameContext* pGameContext{ nullptr };
	int fontHandle{ -1 };

	static constexpr size_t BUTTON_AMOUNT{ 2 };
	std::vector<BuyButton*> btnCollection;
	//商品
	BuyTutorial btnTutorial;
	BuyRepair btnRepairCore;
	BuyTrap btnTrap;
	BuyHolySushi btnHolyLight;
	BuyMap btnMap;

	DxPlus::Vec2Int mousePos{ 0,0 };
	bool prevFrameMouseDown{ false };

	bool isShopOpen{ false };

	//ショップ開店アニメーションに使う
	bool prevShopOpen{ false };
	bool nowShopOpenAnimation{ false };
	void UpdateShopOpenAnimation(float deltaTime);
	void DrawShopOpenAnimation()const;
	DxPlus::Vec2 shopBackgroundPos{ 0,0 };

	unsigned int shopBackgroundColor{ 0 };
};

