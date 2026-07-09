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
    SetMousePoint(DxPlus::CLIENT_WIDTH / 2, (int)DxPlus::CLIENT_HEIGHT / 2);

    bgmHandle = RM().GetMusic(ResourceKeys::Music_Game);
    soundManager->PlayBGM(bgmHandle, 155);

    StartFadeIn();
}

void GameScene::Update(float deltaTime)
{
    gameContext->Update(deltaTime);

#ifndef NDEBUG
    if (CheckHitKey(KEY_INPUT_DELETE))
    {
        Scene* gameOverScene = SceneManager::GetInstance().GetScene(SceneID::GameOver);
        SetNextScene(gameOverScene);
        return;
    }

    if (CheckHitKey(KEY_INPUT_C))
    {
        Scene* gameClearScene = SceneManager::GetInstance().GetScene(SceneID::GameClear);
        SetNextScene(gameClearScene);
        return;
    }
#endif // !NDEBUG


    if (gameContext->GetCore().GetHP() <= 0)
    {
        Scene* gameOverScene = SceneManager::GetInstance().GetScene(SceneID::GameOver);
        SetNextScene(gameOverScene);
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
