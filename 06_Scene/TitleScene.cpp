#include "TitleScene.h"
//#include "../06_Scene/SceneManager.h"
#include "../DxPlus/DxPlus.h"

void TitleScene::Initialize()
{
	SetFontSize(50);
}

void TitleScene::Update(float deltaTime)
{
	//開始ボタンが押されて数秒たったらGamesシーン読み込み
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		//SM().SceneLoadToGame();
	}
}

void TitleScene::Draw() const
{
	int sizeX, sizeY;
	DxLib::GetDrawScreenSize(&sizeX, &sizeY);
	DxPlus::Text::DrawString(
		L"タイトル画面",
		{ static_cast<float>(sizeX / 2), static_cast<float>(sizeY / 2) },
		GetColor(255, 255, 255),
		DxPlus::Text::TextAlign::BOTTOM_CENTER,
		{ 3.0f,3.0f }
	);
}

void TitleScene::End()
{

}
