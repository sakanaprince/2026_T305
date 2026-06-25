// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"

void GameContext::Init()
{
    player.Init();
    stage.Init();
    enemy.Init();

    for (auto& t : turrets)
    {
        t.Init();
    }
    enemy.SetPlayerPointer(&player);
}

void GameContext::Reset()
{
    // 描画先をバックバッファに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    SetBackgroundColor(0, 105, 255);

    player.Reset();
    enemy.SetPosition({ 300,400,300 });
    stage.Reset();

    turrets[0].Reset({ 515, 130, 435 });
    turrets[1].Reset({ -585, 130, 435 });
    turrets[2].Reset({ -585, 130, -670 });
    turrets[3].Reset({ 515, 130, -670 });
}

void GameContext::Update(float deltaTime)
{
    player.Update(deltaTime);  
    enemy.Update(deltaTime);

    for (auto& t : turrets)
    {
        t.Update(deltaTime, player);
    }
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
    for (auto& t : turrets)
    {
        t.Draw();
    }
    player.Draw();
}