#include "../06_Scene/GameOverScene.h"
#include "SceneManager.h"

void GameOverScene::Init()
{
    fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
    backGroundHandle = RM().GetSprite(ResourceKeys::Sprite_GameOverBG);
    bgmHandle = RM().GetMusic(ResourceKeys::Music_GameOver);
    soundClickHandle = RM().GetSound(ResourceKeys::Sound_Click);
    soundManager->PlayBGM(bgmHandle);
    DxLib::SetMouseDispFlag(TRUE);
    buttonTitleColor = buttonNormalColor;
    buttonContinueColor = buttonNormalColor;
    StartFadeIn();
}

void GameOverScene::Update(float deltaTime)
{
    (void)deltaTime;

    using namespace DxPlus::Input;
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    //タイトルボタンの処理
    if (mouseX >= titlePosX_1 && mouseX <= titlePosX_2 && mouseY >= titlePosY_1 && mouseY <= titlePos_Y2)
    {
        buttonTitleColor = buttonOnMouseColor;

        if (GetMouseInput() & MOUSE_INPUT_LEFT)
        {
            soundManager->PlaySENormal(soundClickHandle);
            Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Title);
            SetNextScene(gameScene);
            return;
        }
    }
    else
    {
        buttonTitleColor = buttonNormalColor;
    }

    //コンティニューボタンの処理
    if (mouseX >= continuePosX_1 && mouseX <= continuePosX_2 && mouseY >= continuePosY_1 && mouseY <= continuePos_Y2)
    {
        buttonContinueColor = buttonOnMouseColor;
        if (GetMouseInput() & MOUSE_INPUT_LEFT)
        {
            soundManager->PlaySENormal(soundClickHandle);
            Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Game);
            SetNextScene(gameScene);
            return;
        }
    }
    else
    {
        buttonContinueColor = buttonNormalColor;
    }
}

void GameOverScene::Render() const
{
    DxPlus::Sprite::Draw(backGroundHandle);

    DxPlus::Text::DrawString(L"Game Over",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.25f },
        black, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 4, 4 }, 
        0, fontHandle);


    DrawBox
    (
        (int)titlePosX_1, (int)titlePosY_1,
        (int)titlePosX_2, (int)titlePos_Y2,
        buttonTitleColor,
        true
    );

    DxPlus::Text::DrawString(L"Title",
        { text_TitleX, text_TitleY },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);

    DrawBox
    (
        (int)continuePosX_1, (int)continuePosY_1,
        (int)continuePosX_2, (int)continuePos_Y2,
        buttonContinueColor,
        true
    );

    DxPlus::Text::DrawString(L"Continue",
        { text_ContinueX, text_ContinueY },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);

}
