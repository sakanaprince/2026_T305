#include "Coin.h"

void Coin::Init()
{
	spriteCoin = RM().GetSprite(ResourceKeys::Sprite_Coin);
	fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
}

void Coin::Reset()
{
	currentCoin = 400;
	prevCoin = currentCoin;
	text = std::to_wstring(currentCoin);
}

void Coin::Update()
{
	if (currentCoin != prevCoin)
	{
		text = std::to_wstring(currentCoin);
		prevCoin = currentCoin;
	}
}

void Coin::Draw() const
{
	DrawRotaGraph3(
		10,
		10,
		1.0f,
		1.0f,
		0.05f,
		0.05f,
		0,
		spriteCoin,
		TRUE
	);

	DxPlus::Text::DrawString(
		text.c_str(),
		{ 60, 1.0 },
		GetColor(0, 0, 0),
		DxPlus::Text::TextAlign::TOP_LEFT,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);
	//DrawFormatString(70, 10, GetColor(255, 255, 255), L"%d", currentCoin); 
}
