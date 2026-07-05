#pragma once
#include <string>
class ShopManager;

class BuyButton
{
public:
	BuyButton() = default;
	void Init(ShopManager* shopManager, std::wstring _name, std::wstring _info, int _buyCost, int _fontHandle = -1);
	void Update(float deltaTime);
	void Draw()const;

	void SetButtonPosition(float x, float y)
	{
		buttonPosition_x = x;
		buttonPosition_y = y;
	}


protected:
	//このフレームで商品を購入できたかを返す
	bool CheckBuySuccess(float posX_1, float posX_2, float posY_1, float posY_2);

	//購入成功時の処理...継承先で好きにして
	virtual void PurchaseItem() = 0;

	//Init関数で初期化される変数
	ShopManager* pShopManager{ nullptr };
    std::wstring itemName;
    std::wstring itemInfo;
	int buyCost{ 21 };
	int fontHandle{ -1 };

	bool canBuy{ false };
	bool mouseOnBtn{ false };

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

	//「購入」のエフェクト制御
	//namespaceの代わりの主語的な感じでstructを使用した
	struct BuyEffect
	{
		float effectAliveTimer{ 0.0f };
		const float effectAliveLimit{ 0.5f };
		float effectUpY{ 100.0f };
		bool isEffectAlive{ false };
	};
	
	BuyEffect buyEffect{};
};

