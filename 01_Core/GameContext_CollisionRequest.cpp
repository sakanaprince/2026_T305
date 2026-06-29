// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include "../08_Debug/DebugUI.h"
#include "../10_Physics/Collision.h"

void GameContext::Init()
{
    enemyRoot.Init();
    enemySpawner.Init(&enemyRoot);
    player.Init();
    player.SetBulletPointer(&bullets[0], Const::AMMO_MAX);
    stage.Init();

    for (auto& t : turrets)
    {
        t.Init(&player, &enemy, &coin);
    }
   
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
    enemySpawner.Update(deltaTime);

    for (auto& t : turrets)
    {
        t.Update(deltaTime);
    }

    //2_当たり判定部分のforぶん
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

    stage.Draw();
    for (auto& t : turrets)
    {
        t.Draw();
    }
    for (auto& b : bullets) {
        b.Draw();
    }
    player.Draw();
    enemySpawner.Draw();
}