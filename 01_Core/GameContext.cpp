// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"

void GameContext::Init()
{
    player.Init();
    player.SetBulletPointer(bullets, Const::BULLET_COUNT);
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

    enemyRoot.Init();
    player.Reset();
    for (auto& b : bullets) 
    {
        b.Reset();
    }
    enemy.Init();
    stage.Reset();

    turrets[0].Reset({ 1030,260, 870 });
    turrets[1].Reset({ -1170, 260, 870 });
    turrets[2].Reset({ -1170, 260, -1340 });
    turrets[3].Reset({ 1030, 260, -1340 });
}

void GameContext::Update(float deltaTime)
{
    for (auto& b : bullets) 
    {
        b.Update(deltaTime);
    }
    player.Update(deltaTime);  
    enemy.Update(deltaTime);

    for (auto& t : turrets)
    {
        t.Update(deltaTime, player, enemy);
    }
}

void GameContext::Draw() const
{
    // 画面をクリア
    DxLib::ClearDrawScreen();

    enemy.Draw();
    stage.Draw();
    for (auto& t : turrets)
    {
        t.Draw();
    }
    for (auto& b : bullets) {
        b.Draw();
    }
    player.Draw();
}