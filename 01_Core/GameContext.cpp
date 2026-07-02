// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"
#include "../06_Scene/Scene.h"
#include "../06_Scene/SceneManager.h"

void GameContext::Init()
{
    SetFontSize(50);

    enemyRoot.Init();
    enemy.SetPlayerPointer(&player);
    enemySpawner.Init(&enemyRoot);
    //enemy.Init(&enemyRoot);
    player.Init();
    player.SetBulletPointer(bullets, Const::AMMO_MAX);
    stage.Init();
    coin.Init();
    core.Init();
    for (auto& t : turrets)
    {
        t.Init(&player, &enemySpawner, &coin);
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
    if (limit_Timer <= 0)
    {
        limit_Timer = 0;
    }

    core.Update();
    coin.Update();
    
    for (auto& b : bullets) 
    {
        b.Update(deltaTime);
    }
    player.Update(deltaTime, stage);  
    //enemy.Update(deltaTime);
    enemySpawner.Update(deltaTime);

    for (auto& t : turrets)
    {
        t.Update(deltaTime);
    }

    CollisionEnemyBullet();
    CollisionEnemyArrow();
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

    core.Draw();

    //制限時間の描画
    DrawFormatString(DxPlus::CLIENT_WIDTH  * 0.85f, 10, GetColor(0, 0, 0), L"Time : %.0f", limit_Timer);
}

void GameContext::CollisionEnemyBullet()
{
    for (int i = 0; i < Const::MAX_ENEMY_COUNT; i++)
    {
        auto& en = enemySpawner.GetEnemy(i);
        if (!en) { continue; }

        for (auto& b : bullets)
        {
            if (!b.IsActive()) { continue; }

            if (Collision::IsHitSphereSphere(en->GetSphere(), b.GetBulletSpere()))
            {
                en->TakeDamage(1);
            }

        }
    }
}

void GameContext::CollisionEnemyArrow()
{
    for (int i = 0; i < Const::MAX_ENEMY_COUNT; i++)
    {
        auto& en = enemySpawner.GetEnemy(i);
        if (!en) { continue; }

        for (auto& t : turrets)
        {
            if (t.IsBroken()) { continue; }

            for (int i = 0; i < Const::ARROW_COUNT; i++)
            {
                Arrow& arrow = t.GetArrows(i);
                if (!arrow.IsActive()) { continue; }

                if (Collision::IsHitSphereSphere(en->GetSphere(), arrow.GetSphereArrow()))
                {
                    en->TakeDamage(arrow.GetArrowDamage());
                    arrow.Kill();
                }
            }

        }
    }
}
