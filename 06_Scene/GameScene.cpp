#include "GameScene.h"
#include "SceneManager.h"
#include "../04_Resource/ResourceManager.h"
#include "../04_Resource/ResourceKeys.h"

void GameScene::Init()
{
    DxLib::SetBackgroundColor(32, 32, 32);
    gameContext->Reset();

    StartFadeIn();
}

void GameScene::Update(float deltaTime)
{
    gameContext->Update(deltaTime);

    using namespace DxPlus::Input;
    int buttonDown = GetButtonDown(PLAYER1);
    if (buttonDown & BUTTON_SELECT)
    {
        Scene* resultScene = SceneManager::GetInstance().GetScene(SceneID::Result);
        SetNextScene(resultScene);
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
