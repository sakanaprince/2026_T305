#include "ResultScene.h"
#include "../DxPlus/DxPlus.h"
//#include "SceneManager.h"

void ResultScene::Initialize()
{
}

void ResultScene::Update(float deltaTime)
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        //SM().SceneLoadToTitle();
    }
}

void ResultScene::Draw() const
{
	int sizeX, sizeY;
	DxLib::GetDrawScreenSize(&sizeX, &sizeY);
	DxPlus::Text::DrawString(
		L"ƒŠƒUƒ‹ƒg‰æ–Ê",
		{ static_cast<float>(sizeX / 2), static_cast<float>(sizeY / 2) },
		GetColor(255, 255, 255),
		DxPlus::Text::TextAlign::BOTTOM_CENTER,
		{ 3.0f,3.0f }
	);
}

void ResultScene::End()
{
}
