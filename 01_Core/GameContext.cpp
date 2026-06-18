// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"

void GameContext::Init()
{
    stage.Init();
    enemy.Init();
}

void GameContext::Reset()
{
    // 描画先をバックバッファに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    SetBackgroundColor(0, 105, 255);

    Debug().Log(u8"リセット");

    player.Reset();
    enemy.SetPosition({ 300,400,300 });
    stage.Reset();
}

void GameContext::Update(float deltaTime)
{
    player.Update(deltaTime);
    enemy.Update();
}

void GameContext::Draw() const
{
    // 画面をクリア
    DxLib::ClearDrawScreen();

    const int white = DxLib::GetColor(255, 255, 255);
    DxPlus::Text::DrawString(L"GameScene",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.25f },
        white, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2, 2 }, 0);

    grid.Draw();
    enemy.Draw();
    stage.Draw();
}