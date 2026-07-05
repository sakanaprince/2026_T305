#include "BuyButton.h"
#include "../DxPlus/DxPlus.h"
#include "ShopManager.h"
#include <string>

#include "../01_Core/GameContext.h"

void BuyButton::Init(ShopManager* shopManager, std::wstring _name, std::wstring _info, int _buyCost, int _fontHandle)
{
	pShopManager = shopManager;
	itemName = _name;
	fontHandle = _fontHandle;
	buyCost = _buyCost;
	fontHandle = _fontHandle;

	selectButtonColor = GetColor(150, 190, 150);
	unSelectButtonColor = GetColor(64, 128, 64);
	cantBuyButtonColor = GetColor(255, 80, 44);
}

void BuyButton::Update()
{
	auto gC = pShopManager->GetGameContext();
	canBuy = gC->GetCoinManager().GetCoin() >= buyCost;

	if (ButtonCheckHit(buttonPosition_x, buttonPosition_x + buttonWidth, buttonPosition_y, buttonPosition_y + buttonHeight))
	{
		if (canBuy)
		{
			gC->GetCore().SetHP(gC->GetCore().GetHP() + 30);
			gC->GetCoinManager().MinusCoin(50);
		}
	}
}

void BuyButton::Draw() const
{
	using namespace DxPlus;

	Primitive2D::DrawRect({ buttonPosition_x, buttonPosition_y }, {buttonWidth, buttonHeight}, buttonColor, true);

	wchar_t box[64];
	swprintf(box, sizeof(box) / sizeof(wchar_t),L"%s \n \n %d $",itemName.c_str(), buyCost);

	DxPlus::Text::DrawString(
		box,
		{ 500,500 },
		GetColor(0, 0, 0),
		DxPlus::Text::TextAlign::TOP_LEFT,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);
}

bool BuyButton::ButtonCheckHit(float posX_1, float posX_2, float posY_1, float posY_2)
{
	const DxPlus::Vec2Int mousePos = pShopManager->GetMousePos();

	if (!canBuy)
	{
		buttonColor = cantBuyButtonColor;
		return false;
	}

	if (mousePos.x >= posX_1 && mousePos.x <= posX_2 && mousePos.y >= posY_1 && mousePos.y <= posY_2)
	{
		buttonColor = selectButtonColor;

		//前フレームでクリックされていないことを確認（長押し連続購入防止）
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			if(!pShopManager->GetPrevFrameMouseDown()){ return true; }
		
		}
		return false;
	}

	buttonColor = unSelectButtonColor;
	return false;
	
}
