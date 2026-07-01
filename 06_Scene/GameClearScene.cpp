#include "GameClearScene.h"
#include "SceneManager.h"
#include "../04_Resource/ResourceManager.h"
#include "../04_Resource/ResourceKeys.h"

void GameClearScene::Init()
{
    fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
    backGroundHandle = RM().GetSprite(ResourceKeys::Sprite_GameClearBG);
    DxLib::SetMouseDispFlag(TRUE);
    buttonTitleColor = buttonNormalColor;
    StartFadeIn();
}

void GameClearScene::Update(float deltaTime)
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
            Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Title);
            SetNextScene(gameScene);
            return;
        }
    }
    else
    {
        buttonTitleColor = buttonNormalColor;
    }
}

void GameClearScene::Render() const
{
    DxPlus::Sprite::Draw(backGroundHandle);

    DxPlus::Text::DrawString(L"Game Clear",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.35f },
        black, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 4, 4 },
        0, fontHandle);


    DrawBox
    (
        titlePosX_1, titlePosY_1,
        titlePosX_2, titlePos_Y2,
        buttonTitleColor,
        true
    );

    DxPlus::Text::DrawString(L"Title",
        { text_TitleX, text_TitleY },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);
}
