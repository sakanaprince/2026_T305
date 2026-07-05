#pragma once
#include <string>
class ShopManager;

class BuyButton
{
public:
	BuyButton() = default;
	void Init(ShopManager* shopManager, std::wstring _name, std::wstring _info, int _buyCost, int _fontHandle = -1);
	void Update();
	void Draw()const;

private:
	bool ButtonCheckHit(float posX_1, float posX_2, float posY_1, float posY_2);

	ShopManager* pShopManager{ nullptr };
    std::wstring itemName;
    std::wstring itemInfo;
	int buyCost{ 21 };
	int fontHandle{ -1 };

	bool canBuy{ false };

	//予測変換出てこなくて嫌なので個別のfloatで持つ
	float buttonPosition_x{ 500.0f };
	float buttonPosition_y{ 500.0f };
	float buttonWidth{ 384.0f };
	float buttonHeight{ 256.0f };

	//ボタンの色
	unsigned int buttonColor{ 0 };
	unsigned int selectButtonColor{ 0 };
	unsigned int unSelectButtonColor{ 0 };
	unsigned int cantBuyButtonColor{ 0 };
};

