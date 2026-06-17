#include "GameContext.h"

void GameContext::Init()
{
}

void GameContext::Reset()
{
    // 描画先をバックバッファに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);

}

void GameContext::Update(float deltaTime)
{
}

void GameContext::Draw() const
{
    // 画面をクリア
    DxLib::ClearDrawScreen();

    const int white = DxLib::GetColor(255, 255, 255);
    DxPlus::Text::DrawString(L"GameScene",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.25f },
        white, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2, 2 }, 0);
}