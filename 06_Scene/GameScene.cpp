#include "GameScene.h"
#include "../DxPlus/DxPlus.h"

void GameScene::Initialize()
{
}

void GameScene::Update(float deltaTime)
{ 
}

void GameScene::Draw() const
{
	int sizeX, sizeY;
	DxLib::GetDrawScreenSize(&sizeX, &sizeY);
	DxPlus::Text::DrawString(
		L"ÉQÅ[ÉÄâÊñ ",
		{ static_cast<float>(sizeX / 2), static_cast<float>(sizeY / 2) },
		GetColor(255, 255, 255),
		DxPlus::Text::TextAlign::BOTTOM_CENTER,
		{ 3.0f,3.0f }
	);
}

void GameScene::End()
{
}


