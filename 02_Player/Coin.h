#pragma once
#include "../04_Resource/ResourceManager.h"

#include <string>

class Coin
{
public:
	Coin() = default;
	~Coin() = default;

	void Init();
	void Reset();
	void Update();
	void Draw() const;

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
	int fontHandle{ -1 };

	int currentCoin{ 0 };
	int prevCoin{ 0 };

	std::wstring text;
};

