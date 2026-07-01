// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"
#include "../06_Scene/Scene.h"
#include "../06_Scene/SceneManager.h"

void GameContext::Init()
{
    enemyRoot.Init();
    enemy.SetPlayerPointer(&player);
    enemySpawner.Init(&enemyRoot);
    //enemy.Init(&enemyRoot);
    player.Init();
    player.SetBulletPointer(bullets, Const::AMMO_MAX);
    stage.Init();
    coin.Init();
    for (auto& t : turrets)
    {
        t.Init(&player, &enemy, &coin);
    }
}

void GameContext::Reset()
{
    limit_Timer = limit_Time;

    // 描画先をバックバッファに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    SetBackgroundColor(0, 105, 255);

    player.Reset();
    for (auto& b : bullets) 
    {
        b.Reset();
    }
    stage.Reset();

    enemy.Reset();

    turrets[0].Reset({ 1030,260, 870 });
    turrets[1].Reset({ -1170, 260, 870 });
    turrets[2].Reset({ -1170, 260, -1340 });
    turrets[3].Reset({ 1030, 260, -1340 });

    coin.Reset();
    core.Reset();
}

void GameContext::Update(float deltaTime)
{
    limit_Timer -= deltaTime;

    for (auto& b : bullets) 
    {
        b.Update(deltaTime);
    }
    player.Update(deltaTime);  
    //enemy.Update(deltaTime);
    enemySpawner.Update(deltaTime);

    for (auto& t : turrets)
    {
        t.Update(deltaTime);
    }

    for (int i = 0; i < Const::MAX_ENEMY_COUNT; i++)
    {
        EnemyLow& en = enemySpawner.GetEnemy(i);

        if (!en.IsAlive()) { continue; }

        for (auto& b : bullets)
        {
            if (!b.IsActive()) { continue; }

            if (Collision::IsHitSphereSphere(en.GetSphere(), b.GetRadius()))
            {
                en.TakeDamage(1);
            }

        }
    }
}

void GameContext::Draw() const
{
    // 画面をクリア
    DxLib::ClearDrawScreen();

    //enemy.Draw();
    enemySpawner.Draw();
    stage.Draw();
    for (auto& t : turrets)
    {
        t.Draw();
    }
    for (auto& b : bullets) {
        b.Draw();
    }
    coin.Draw();
    player.Draw();

    //制限時間の描画
    DrawLine(0, 75, DxPlus::CLIENT_WIDTH * 0.5 - 60, 75, GetColor(0, 0, 0), 2);
    DrawLine(DxPlus::CLIENT_WIDTH * 0.5 + 60, 75, DxPlus::CLIENT_WIDTH, 75, GetColor(0, 0, 0), 2);

    DrawCircle(DxPlus::CLIENT_WIDTH * 0.5, 75, 60, GetColor(0, 0, 0), false, 2);

    int fontSize = 50;
    SetFontSize(fontSize);
    DrawFormatString(DxPlus::CLIENT_WIDTH * 0.5f - fontSize + 10, 50, GetColor(0, 0, 0), L"%.0f", limit_Timer);
}