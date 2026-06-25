#include "TitleScene.h"
#include "../04_Resource/ResourceManager.h"
#include "SceneManager.h"
#include "../04_Resource/ResourceKeys.h"

void TitleScene::Init()
{
//    frameCount = 0;
    fontHandle = RM().GetFont(ResourceKeys::Font_Title);
    backGroundHandle = RM().GetSprite(ResourceKeys::Sprite_TitleBG);
    StartFadeIn();

    blinkTimer = BLINK_INTERVAL;
    isPushEnterVisible = false;
}

void TitleScene::Update(float deltaTime)
{
    using namespace DxPlus::Input;
    if (GetButtonDown(PLAYER1) & BUTTON_START)
    {
        Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Game);
        SetNextScene(gameScene);
        return;
    }

    // PushEnter‚Ì“_–Å
    blinkTimer -= deltaTime;
    if (blinkTimer <= 0.0f)
    {
        blinkTimer += BLINK_INTERVAL;
        isPushEnterVisible = !isPushEnterVisible;
    }
}

void TitleScene::Render() const
{
    DxPlus::Sprite::Draw(backGroundHandle);

    const int black = DxLib::GetColor(0, 0, 0);
    DxPlus::Text::DrawString(L"Tower Difense",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.35f },
        black, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);


    const int yellow = DxLib::GetColor(255, 255, 0);
    if (isPushEnterVisible)
    {
        DxPlus::Text::DrawString(L"Push Enter",
            { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.75f },
            yellow, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 1,1 }, 0, fontHandle);
    }
}
