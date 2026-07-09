#include "BuyButton.h"
#include "../DxPlus/DxPlus.h"
#include "ShopManager.h"
#include <string>

#include "../01_Core/GameContext.h"
#include "../04_Resource/ResourceManager.h"
void BuyButton::Init(ShopManager* shopManager, std::wstring _name, std::wstring _info, int _buyCost, int _fontHandle)
{
	pShopManager = shopManager;
	itemName = _name;
	itemInfo = _info;
	fontHandle = _fontHandle;
	buyCost = _buyCost;
	fontHandle = _fontHandle;

	selectButtonColor = GetColor(150, 190, 150);
	unSelectButtonColor = GetColor(64, 128, 64);
	cantBuyButtonColor = GetColor(255, 80, 44);
}

void BuyButton::Update(float deltaTime)
{
	auto gC = pShopManager->GetGameContext();
	canBuy = gC->GetCoinManager().GetCoin() >= buyCost;

	//購入処理
	if (CheckBuySuccess(buttonPosition_x, buttonPosition_x + buttonWidth, buttonPosition_y, buttonPosition_y + buttonHeight))
	{
		buyEffect.isEffectAlive = true;
		buyEffect.effectAliveTimer = 0.0f;
		buyEffect.effectUpY = buttonPosition_y;
		gC->GetCoinManager().MinusCoin(buyCost);
		pushedUXTimer = PushedUXTime;

		gC->GetSoundManager().PlaySENormal(RM().GetSound(ResourceKeys::Sound_BuyItem));
		//継承を使ったら解決できそう(できました
		PurchaseItem();
	}

	//購入エフェクト更新
	if (buyEffect.isEffectAlive)
	{
		constexpr float effectSpeed = 256.0f;
		buyEffect.effectUpY -= effectSpeed * deltaTime;
		buyEffect.effectAliveTimer += deltaTime;

		if(buyEffect.effectAliveTimer >= buyEffect.effectAliveLimit){ buyEffect.isEffectAlive = false; }
	}

	//ボタンUXアニメーション
	currentUXState = mouseOnBtn ? UXState::toReduce : UXState::toExpand;
	
	if(pushedUXTimer > 0.0f)
	{
		pushedUXTimer -= deltaTime;
		scale -= deltaTime * ScaleSpeed;
		scale = std::max(scale, MinReduceEndScale);
		return;
	}

	else if (currentUXState == UXState::toReduce)
	{
		scale -= deltaTime * ScaleSpeed;
		
		scale = std::max(scale, ReduceEndScale);
	}
	else if(currentUXState == UXState::toExpand)
	{
		scale += deltaTime * ScaleSpeed;

		scale = std::min(scale, ExpandEndScale);
	}
}

void BuyButton::Draw() const
{
	using namespace DxPlus;

	Primitive2D::DrawRect({ buttonPosition_x, buttonPosition_y }, 
		{buttonWidth * scale, buttonHeight * scale}, buttonColor, true	);

	//目標 * 　影響度でできないかな
	//int rightEnd = buttonPosition_x + 30;

	//DxLib::DrawBox(
	//	buttonPosition_x + (scale * power),
	//	buttonPosition_y,
	//	buttonPosition_x + buttonWidth,
	//	buttonPosition_y + buttonHeight,
	//	buttonColor,
	//	true
	//);

	wchar_t box[64];
	swprintf(box, sizeof(box) / sizeof(wchar_t),L"%s \n \n %d $",itemName.c_str(), buyCost);

	DxPlus::Text::DrawString(
		box,
		{ buttonPosition_x, buttonPosition_y },
		GetColor(0, 0, 0),
		DxPlus::Text::TextAlign::TOP_LEFT,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);

	if (mouseOnBtn)
	{
		DxPlus::Text::DrawString(
			itemInfo.c_str(),
			{ DxPlus::CLIENT_WIDTH * 0.1f,DxPlus::CLIENT_HEIGHT * 0.8f },
			GetColor(255, 255,255),
			DxPlus::Text::TextAlign::TOP_LEFT,
			{ 1.5f,1.5f },
			0.0,
			-1);
	}

	if (buyEffect.isEffectAlive)
	{
		DxPlus::Text::DrawString(
			L"Purchased",
			{ buttonPosition_x, buyEffect.effectUpY },
			GetColor(100, 105, 10),
			DxPlus::Text::TextAlign::TOP_LEFT,
			{ 1.5f,1.5f },
			-10 * Deg2Rad,
			fontHandle);
	}
}

bool BuyButton::CheckBuySuccess(float posX_1, float posX_2, float posY_1, float posY_2)
{
	const DxPlus::Vec2Int mousePos = pShopManager->GetMousePos();
	mouseOnBtn = false;


	if (!canBuy)
	{
		buttonColor = cantBuyButtonColor;
		return false;
	}


	if (mousePos.x >= posX_1 && mousePos.x <= posX_2 && mousePos.y >= posY_1 && mousePos.y <= posY_2)
	{
		mouseOnBtn = true;
		buttonColor = selectButtonColor;

		//前フレームでクリックされていないことを確認（長押し連続購入防止）
		if (!pShopManager->GetPrevFrameMouseDown() && GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			if (canBuy) { return true; }

		}
		return false;
	}


	
	buttonColor = unSelectButtonColor;
	return false;
	
}
