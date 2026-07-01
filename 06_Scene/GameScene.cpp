#include "GameScene.h"
#include "SceneManager.h"
#include "../04_Resource/ResourceManager.h"
#include "../04_Resource/ResourceKeys.h"

void GameScene::Init()
{
    DxLib::SetBackgroundColor(32, 32, 32);
    gameContext->Reset();

    //ƒ}ƒEƒX‚ðÁ‚·‚©‚ÌÝ’è
    DxLib::SetMouseDispFlag(FALSE);
    SetMousePoint(DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.5f);

    StartFadeIn();
}

void GameScene::Update(float deltaTime)
{
    gameContext->Update(deltaTime);

    int mouseX;
    int mouseY;
    GetMousePoint(&mouseX, &mouseY);
    if (mouseX >= DxPlus::CLIENT_WIDTH - 1)
    {
        SetMousePoint(0, mouseY);
    }
    else if (mouseX <= 0)
    {
        SetMousePoint(DxPlus::CLIENT_WIDTH - 1, mouseY);
    }

    if (gameContext->GetCore().GetHP() <= 0)
    {
        Scene* gameClearScene = SceneManager::GetInstance().GetScene(SceneID::GameOver);
        SetNextScene(gameClearScene);
        return;
    }

    if (gameContext->GetLimit_Timer() <= 0)
    {
        Scene* gameClearScene = SceneManager::GetInstance().GetScene(SceneID::GameClear);
        SetNextScene(gameClearScene);
        return;
    }
}

void GameScene::Render() const
{
    gameContext->Draw();
}

void GameScene::End()
{
}
