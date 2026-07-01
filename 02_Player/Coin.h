#pragma once

class Coin
{
public:
	Coin() = default;
	~Coin() = default;

	void Reset() { currentCoin = 200; }

	void PlusCoin(int getCoin) { currentCoin += getCoin; }
	void MinusCoin(int minusCoin) 
	{
		currentCoin -= minusCoin;
		if (currentCoin <= 0) { currentCoin = 0; }
	}

	int  GetCoin() { return currentCoin; }

private:
	int currentCoin{ 0 };
};

