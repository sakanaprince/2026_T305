#include "ShopManager.h"
#include "../DxPlus/DxPlus.h"
#include "../04_Resource/ResourceManager.h"

void ShopManager::Init(GameContext* gC)
{
	pGameContext = gC;

	fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);

	btnRepairCore.Init(this, L"Core Repair", L"コアを50回復します", 50, fontHandle);
}

void ShopManager::Update()
{
	GetMousePoint(&mousePos.x, &mousePos.y);

	btnRepairCore.Update();

	//左クリックが前フレームされたか確認
	int mouseBtnLeftDown = GetMouseInput();

	prevFrameMouseDown = (mouseBtnLeftDown & MOUSE_INPUT_LEFT);
}

void ShopManager::Draw()const
{
	using namespace DxPlus;

	//ショップの背景
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	Primitive2D::DrawRect({ 0,0 }, { CLIENT_WIDTH, CLIENT_HEIGHT }, GetColor(255, 255, 255), true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	
	SetFontSize(70);
	wchar_t box[64];
	swprintf(box, sizeof(box) / sizeof(wchar_t), L"W E L C O M E  T O  S H O P");

	DxPlus::Text::DrawString(
		box,
		{DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.9f},
		GetColor(0, 0, 0),
		DxPlus::Text::TextAlign::TOP_LEFT,
		{ 1.5f,1.5f },
		0.0,
		fontHandle);
	btnRepairCore.Draw();

}
