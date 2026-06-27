// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"

void GameContext::Init()
{
    enemyRoot.Init();
    enemy.Init(&enemyRoot);
    player.Init();
    player.SetBulletPointer(bullets, Const::BULLET_COUNT);
    stage.Init();

    for (auto& t : turrets)
    {
        t.Init(&player, &enemy, &coin);
    }
    enemy.SetPlayerPointer(&player);
}

void GameContext::Reset()
{

    // 描画先をバックバッファに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    SetBackgroundColor(0, 105, 255);

    player.Reset();
    for (auto& b : bullets) 
    {
        b.Reset();
    }
    stage.Reset();

    enemy.Reset({ 500,500,500 }, 0);

    turrets[0].Reset({ 1030,260, 870 });
    turrets[1].Reset({ -1170, 260, 870 });
    turrets[2].Reset({ -1170, 260, -1340 });
    turrets[3].Reset({ 1030, 260, -1340 });

    coin.Reset();
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
        t.Update(deltaTime);
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