#pragma once
#include "BuyButton.h"
#include "../DxPlus/DxPlus.h"

class GameContext;

class ShopManager
{
public:
	ShopManager() = default;
	void Init(GameContext* gC);
	void Update();
	void Draw()const;

	bool IsShopOpen(){ return isShopOpen; }
	void SwitchShopOpen() { isShopOpen = !isShopOpen; }
	const bool GetPrevFrameMouseDown()const  { return prevFrameMouseDown; }

	GameContext* GetGameContext() { return pGameContext; }
	const DxPlus::Vec2Int& GetMousePos() const{ return mousePos; }

private:
	GameContext* pGameContext{ nullptr };
	int fontHandle{ -1 };
	BuyButton btnRepairCore;
	DxPlus::Vec2Int mousePos{ 0,0 };
	bool isShopOpen{ false };
	bool prevFrameMouseDown{ false };
};

