#include "TitleScene.h"
#include "../04_Resource/ResourceManager.h"
#include "SceneManager.h"
#include "../04_Resource/ResourceKeys.h"

void TitleScene::Init()
{
//    frameCount = 0;
    fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
    backGroundHandle = RM().GetSprite(ResourceKeys::Sprite_TitleBG);
    buttonColor = buttonNormalColor;
    StartFadeIn();

    DxLib::SetMouseDispFlag(TRUE);
}

void TitleScene::Update(float deltaTime)
{
    using namespace DxPlus::Input;
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    if (mouseX >= posX_1 && mouseX <= posX_2 && mouseY >= posY_1 && mouseY <= pos_Y2)
    {
        buttonColor = buttonOnMouseColor;

        if (GetMouseInput() & MOUSE_INPUT_LEFT)
        {
            Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Game);
            SetNextScene(gameScene);
            return;
        }
    }
    else
    {
        buttonColor = buttonNormalColor;
    }
}

void TitleScene::Render() const
{
    DxPlus::Sprite::Draw(backGroundHandle);

    DxPlus::Text::DrawString(L"Tower Difense",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.35f },
        black, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 4,4 }, 0, fontHandle);

    DrawBox
    (
        posX_1, posY_1,
        posX_2, pos_Y2,
        buttonColor,
        true
    );

    DxPlus::Text::DrawString(L"Game Start",
        { text_StartX, text_StartY },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);
}
