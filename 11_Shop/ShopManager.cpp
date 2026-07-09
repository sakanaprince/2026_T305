#include "ShopManager.h"
#include "../DxPlus/DxPlus.h"
#include "../04_Resource/ResourceManager.h"
#include "../01_Core/GameContext.h"


void ShopManager::Init(GameContext* gC)
{
	pGameContext = gC;

	fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
	btnTutorial.Init(this, L"Help?", L"WASD移動_Eショップ_Rリロード_左クリック攻撃_Shiftダッシュ_Enter罠を配置",0, fontHandle);
	btnRepairCore.Init(this, L"Core Repair", L"コア耐久力を30回復します。こればかり購入するとお金が貯まりません...。", 50, fontHandle);
	btnTrap.Init(this, L"Ground Trap", L"罠です。地面に設置するタイプのシンプルなやつです。", 100, fontHandle);
	btnHolyLight.Init(this, L"Holy Light", L"聖なる光です。全ての敵を滅ぼそうとします。", 500, fontHandle);
	btnMap.Init(this, L"Radar Eye", L"レーダーです。コアと敵の位置を教えてくれます。", 150, fontHandle);

	btnCollection.clear();
	btnCollection.push_back(&btnTutorial);
	btnCollection.push_back(&btnRepairCore);
	btnCollection.push_back(&btnTrap);
	btnCollection.push_back(&btnMap);
	btnCollection.push_back(&btnHolyLight);

	constexpr int basePosX = 100;
	constexpr int distanceX = 400;
	constexpr int basePosY = 200;
	constexpr int basePosY_2 = 650;
	int roop = 0;
	for (auto& b : btnCollection)
	{
		int y = roop >= 3 ? basePosY_2 : basePosY;
		b->SetButtonPosition(basePosX + (distanceX * (roop % 3)), y);

		roop++;
	}

	shopBackgroundColor = GetColor(200, 200, 210);
}

void ShopManager::Update(float deltaTime)
{
	//開いた直後
	if (isShopOpen && !prevShopOpen)
	{
		nowShopOpenAnimation = true;
		pGameContext->GetSoundManager().PlaySENormal(RM().GetSound(ResourceKeys::Sound_OpenShop));
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
	swprintf(box, sizeof(box) / sizeof(wchar_t), L"W E L C O M E   T O . . .    S H O P");
	DxPlus::Text::DrawString(
		box,
		{ DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.1f },
		GetColor(0, 0, 128),
		DxPlus::Text::TextAlign::TOP_CENTER,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);
	
	const int coin = pGameContext->GetCoinManager().GetCoin();

	swprintf(box, sizeof(box) / sizeof(wchar_t), L"Coin : %d",coin);
	DxPlus::Text::DrawString(
		box,
		{ DxPlus::CLIENT_WIDTH * 0.1f, DxPlus::CLIENT_HEIGHT * 0.9f },
		GetColor(64, 64, 4),
		DxPlus::Text::TextAlign::TOP_LEFT,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);
	//DxLib::DrawFormatString(DxPlus::CLIENT_WIDTH * 0.1f, DxPlus::CLIENT_HEIGHT * 0.9,
	//	GetColor(0,0,0), L"COIN : %d", coin
	//);


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
