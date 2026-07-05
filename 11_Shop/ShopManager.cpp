#include "ShopManager.h"
#include "../DxPlus/DxPlus.h"
#include "../04_Resource/ResourceManager.h"
#include "../01_Core/GameContext.h"

void ShopManager::Init(GameContext* gC)
{
	pGameContext = gC;

	fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
	btnRepairCore.Init(this, L"Core Repair", L"コア耐久力を30回復します。こればかり購入するとお金が貯まりません...。", 50, fontHandle);
	btnRepairCore.SetButtonPosition(100, 500);
	btnSushi.Init(this, L"Sushi", L"お寿司です。美味しい。", 10, fontHandle);
	btnSushi.SetButtonPosition(600, 500);

	btnCollection.clear();
	btnCollection.push_back(&btnRepairCore);
	btnCollection.push_back(&btnSushi);

	shopBackgroundColor = GetColor(200, 200, 210);
}

void ShopManager::Update(float deltaTime)
{
	//開いた直後
	if (isShopOpen && !prevShopOpen)
	{
		nowShopOpenAnimation = true;
		shopBackgroundPos = { -DxPlus::CLIENT_WIDTH, 0 };
	}

	prevShopOpen = isShopOpen;

	if (nowShopOpenAnimation) 
	{ 
		UpdateShopOpenAnimation(deltaTime);
		return;
	}

	if (!isShopOpen) { return; }

	GetMousePoint(&mousePos.x, &mousePos.y);

	for (const auto& b : btnCollection) { b->Update(deltaTime); }

	//左クリックが前フレームされたか確認
	int mouseBtnLeftDown = GetMouseInput();

	prevFrameMouseDown = (mouseBtnLeftDown & MOUSE_INPUT_LEFT);
}

void ShopManager::Draw()const
{
	if (!isShopOpen) { return; }

	if (nowShopOpenAnimation)
	{
		DrawShopOpenAnimation();
		return;
	}

	using namespace DxPlus;

	//ショップの背景
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 240);
	Primitive2D::DrawRect({ 0,0 }, { CLIENT_WIDTH, CLIENT_HEIGHT }, shopBackgroundColor, true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Primitive2D::DrawRect({ 0,CLIENT_HEIGHT * 0.795f }, { CLIENT_WIDTH,50.0f }, GetColor(0, 0, 0));

	//個別ボタンのDraw
	for (const auto& b : btnCollection){ b->Draw();}

	SetFontSize(70);
	wchar_t box[64];
	swprintf(box, sizeof(box) / sizeof(wchar_t), L"W E L C O M E  T O  S H O P");
	DxPlus::Text::DrawString(
		box,
		{ DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.1f },
		GetColor(0, 0, 128),
		DxPlus::Text::TextAlign::TOP_LEFT,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);
	
	const int coin = pGameContext->GetCoinManager().GetCoin();
	DxLib::DrawFormatString(DxPlus::CLIENT_WIDTH * 0.1f, DxPlus::CLIENT_HEIGHT * 0.9,
		GetColor(0,0,0), L"COIN : %d", coin
	);
	int a = 1;

}

void ShopManager::UpdateShopOpenAnimation(float deltaTime)
{
	shopBackgroundPos.x += deltaTime * DxPlus::CLIENT_WIDTH * 2;

	if (shopBackgroundPos.x >= 0) 
	{	
		shopBackgroundPos.x = 0;
		nowShopOpenAnimation = false;
	}
}

void ShopManager::DrawShopOpenAnimation() const
{
	using namespace DxPlus;
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	Primitive2D::DrawRect({  shopBackgroundPos.x , shopBackgroundPos.y }, { CLIENT_WIDTH, CLIENT_HEIGHT }, shopBackgroundColor, true);
	Primitive2D::DrawRect({ -shopBackgroundPos.x , shopBackgroundPos.y }, { CLIENT_WIDTH, CLIENT_HEIGHT }, shopBackgroundColor, true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
