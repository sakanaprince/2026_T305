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
    fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
    trapModelHandle = RM().GetModel(ResourceKeys::Model_Trap);

    stage.Init();
    coin.Init();
    core.Init();
    for (auto& t : turrets)
    {
        t.Init(&player, &enemySpawner, &coin);
    }
    enemyRoot.Init();
    enemySpawner.Init(&enemyRoot, &player, this);
    bullets->Init();   
    player.Init();
    player.SetBulletPointer(bullets, Const::AMMO_MAX);
    shopManager.Init(this);
}

void GameContext::Reset()
{
    // 描画先をバックバッファに指定
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    SetBackgroundColor(0, 105, 255);

    limit_Timer = limit_Time;
    limit_prevTime = limit_Timer;
    
    text_Timer = std::to_wstring(static_cast<int>(limit_Timer));

    possessionTrap = 0;
    
    stage.Reset();
    coin.Reset();
    core.Reset();
    turrets[0].Reset({ 1100,300, 1100 });
    turrets[1].Reset({ -1100, 300, 1100 });
    turrets[2].Reset({ -1100, 300, -1100 });
    turrets[3].Reset({ 1100, 300, -1100 });
    player.Reset();
    for (auto& b : bullets) 
    {
        b.Reset();
    }
}

void GameContext::Update(float deltaTime)
{ 
    TimeLimit(deltaTime);

    //テスト用
    int buttonDown = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
    if (buttonDown & DxPlus::Input::BUTTON_L1)
    {
        BuyTrap();
        Debug().Log(u8"現在のトラップの所持数トラップ", possessionTrap);
    }
    //---

    InstallationTrap();

    core.Update();
    coin.Update();
    for (auto& t : turrets)
    {
        t.Update(deltaTime);
    }
    
    for (auto& b : bullets) 
    {
        b.Update(deltaTime);
    }

    player.Update(deltaTime, stage);  
    enemySpawner.Update(deltaTime);

    //shopManager.Update();

    CollisionEnemyBullet();
    CollisionEnemyArrow();
    CollisionEnemyTrap();
}

void GameContext::Draw() const
{
    // 画面をクリア
    DxLib::ClearDrawScreen();

    stage.Draw();
    coin.Draw();
    core.Draw();
    for (auto& t : turrets)
    {
        t.Draw();
    }
    enemySpawner.Draw();
    for (auto& b : bullets) {
        b.Draw();
    }
    player.Draw();

    //shopManager.Draw();


    DxPlus::Text::DrawString(
        (L"Time : "+ text_Timer).c_str(),
        { DxPlus::CLIENT_WIDTH * 0.93f, 20 },
        GetColor(0, 0, 0),
        DxPlus::Text::TextAlign::TOP_CENTER,
        { 1.5f,1.5f },
        0.0,
        fontHandle);

    SetFontSize(30);
    DrawFormatString(10, DxPlus::CLIENT_HEIGHT * 0.95f, GetColor(255, 255, 255), 
        L"移動：WASD　射撃：左クリック　武器変更：マウスホイール　リロード：R　ダッシュ：左Shift　ジャンプ：Space");
    SetFontSize(50);

    if (spawnTraps.size() > 0)
    {
        for (auto& t : spawnTraps)
        {
            t->Draw();
        }
    }
}

void GameContext::TimeLimit(float deltaTime)
{
    limit_Timer -= deltaTime;
    if (limit_Timer <= 0)
    {
        limit_Timer = 0;
    }

    //1秒ごとにテキストを変更する
    if (limit_Timer <= limit_prevTime)
    {
        limit_prevTime--;
        text_Timer = std::to_wstring(static_cast<int>(limit_Timer));

        if (limit_prevTime > 0) { return; }

        limit_prevTime = 0;
    }
}

void GameContext::CollisionEnemyBullet()
{
    for (int i = 0; i < enemySpawner.GetEnemyCollectionSize(); i++)
    {
        auto& en = enemySpawner.GetEnemy(i);
        if (!en) { continue; }
        if (!en->IsAlive()) { continue; }

        for (auto& b : bullets)
        {
            if (!b.IsActive()) { continue; }

            if (Collision::IsHitSphereSphere(en->GetSphere(), b.GetBulletSpere()))
            {
                en->TakeDamage(b.BulletDamage());
                b.DeActivate();
            }

        }
    }
}

void GameContext::CollisionEnemyArrow()
{
    for (int i = 0; i < enemySpawner.GetEnemyCollectionSize(); i++)
    {
        auto& en = enemySpawner.GetEnemy(i);
        if (!en) { continue; }
        if (!en->IsAlive()) { continue; }

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

void GameContext::CollisionEnemyTrap()
{
    for (int i = 0; i < enemySpawner.GetEnemyCollectionSize(); i++)
    {
        auto& en = enemySpawner.GetEnemy(i);
        if (!en) { continue; }
        if (!en->IsAlive()) { continue; }

        for (auto& t : spawnTraps)
        {
            if (Collision::IsHitSphereBox(en->GetSphere(), t->GetBox()))
            {
                en->TakeDamage(1);
            }
        }

    }
}

void GameContext::InstallationTrap()
{
    int buttonDown = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);

    if (buttonDown & DxPlus::Input::BUTTON_START)
    {
        //現在の所持しているトラップが数が０の場合とプレイヤーが地面にいない場合は処理をしない
        if (possessionTrap == 0) { return; }


        //if (!player.IsGrounded()) { return; }  //プレイヤーのisGroundedのゲッターができてから使う


        bool isHit = false;

        //現在設置しているトラップが一つでもあれば設置しているトラップと被らないように当たり判定をチェックする
        if (spawnTraps.size() > 0)
        {
            Collision::Box box;
            box.centerPos = player.GetPosition();
            box.scale = spawnTraps[0]->GetHitScale();

            for (auto& t : spawnTraps)
            {
                if (Collision::IsHitBoxBox(box, t->GetBox()))
                {
                    isHit = true;
                    break;
                }
            }
        }

        //他のトラップと当たり判定が被っていたら設置できないようにする
        if (!isHit)
        {
            spawnTraps.push_back(std::make_unique<Trap>(trapModelHandle, player.GetPosition()));
            possessionTrap--;
            if (possessionTrap <= 0) { possessionTrap = 0; }
            Debug().Log(u8"現在のトラップの所持数トラップ", possessionTrap);
        }
    }

}
