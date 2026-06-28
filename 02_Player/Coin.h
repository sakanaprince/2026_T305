#pragma once
#include "../04_Resource/ResourceManager.h"

class Coin
{
public:
	Coin() = default;
	~Coin() = default;

	void Init() { spriteCoin = RM().GetSprite(ResourceKeys::Sprite_Coin); }
	void Reset() { currentCoin = 200; }
	void Draw() const
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
		DrawFormatString(70, 10, GetColor(255, 255, 255), L"%d", currentCoin); 
	}

	void PlusCoin(int getCoin) { currentCoin += getCoin; }
	void MinusCoin(int minusCoin) 
	{
		currentCoin -= minusCoin;
		if (currentCoin <= 0) { currentCoin = 0; }
	}

	int  GetCoin() { return currentCoin; }
	int GetCoinSprite() { return spriteCoin; }

private:
	int spriteCoin{ -1 };
	int currentCoin{ 0 };
};

