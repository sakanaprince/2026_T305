#include "TitleScene.h"
#include "../04_Resource/ResourceManager.h"
#include "SceneManager.h"
#include "../04_Resource/ResourceKeys.h"

void TitleScene::Init()
{
//    frameCount = 0;
    fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
    backGroundHandle = RM().GetSprite(ResourceKeys::Sprite_TitleBG);
    tutorial_PurposeHandle = RM().GetSprite(ResourceKeys::Sprite_TutorialPurpose);
    tutorial_TurretReleaseHandle = RM().GetSprite(ResourceKeys::Sprite_TutorialTurretRelease);
    tutorial_TurretUpgradeHandle = RM().GetSprite(ResourceKeys::Sprite_TutorialTurretUpgrade);
    titleButtonColor = buttonNormalColor;
    tutorialButtonColor = buttonNormalColor;
    nextButtonColor = buttonNormalColor;
    returnButtonColor = buttonNormalColor;
    mouseIntervalTimer = mouseInterval;
    tutorial = 0;
    StartFadeIn();

    DxLib::SetMouseDispFlag(TRUE);
}

void TitleScene::Update(float deltaTime)
{
    using namespace DxPlus::Input;
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    if (tutorial == Tutorial::Title)
    {
        if (ButtonCheckHit(mouseX, mouseY, titlePosX_1, titlePosX_2, titlePosY_1, titlePosY_2, titleButtonColor))
        {
            //タイトルボタンの判定
            Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Game);
            SetNextScene(gameScene);
            return;

        }

        //チュートリアルボタンの判定
        if (ButtonCheckHit(mouseX, mouseY, tutorialPosX_1, tutorialPosX_2, tutorialPosY_1, tutorialPosY_2, tutorialButtonColor))
        {
            titleButtonColor = buttonNormalColor;
            tutorial = 1;
        }

    }
    else
    {
        mouseIntervalTimer -= deltaTime;

        if (ButtonCheckHit(mouseX, mouseY, nextPosX_1, nextPosX_2, nextPosY_1, nextPosY_2, nextButtonColor))
        {
            tutorial++;
            
            if (tutorial == Tutorial::None)
            {
                tutorial = 0;
            }

            mouseIntervalTimer = mouseInterval;
        }


        if (ButtonCheckHit(mouseX, mouseY, returnPosX_1, returnPosX_2, returnPosY_1, returnPosY_2, returnButtonColor))
        {
            tutorial--;

            mouseIntervalTimer = mouseInterval;
        }
    }
}

void TitleScene::Render() const
{
    switch (tutorial)
    {
    case Title:
        TitleRender();
        break;
    case Purpose:
        TutorialPurposeRender();
        break;
    case Operation:
        TutorialOperation();
        break;
    case Turret_Release:
        TutorialTurretRelease();
        break;
    case Turret_Upgrade:
        TutorialTurretUpgrade();
        break;
    }

    //チュートリアル画面の時は常に画面左下と右下にボタンを表示する
    if (tutorial != Tutorial::Title)
    {
        DrawBox
        (
            nextPosX_1, nextPosY_1,
            nextPosX_2, nextPosY_2,
            nextButtonColor,
            true
        );

        DxPlus::Text::DrawString(L"Next",
            { text_NextX, text_NextY },
            textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);

        DrawBox
        (
            returnPosX_1, returnPosY_1,
            returnPosX_2, returnPosY_2,
            returnButtonColor,
            true
        );

        DxPlus::Text::DrawString(L"Return",
            { text_returnX, text_returnY },
            textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);
    }
}

bool TitleScene::ButtonCheckHit(int mouseX, int mouseY, float posX_1, float posX_2, float posY_1, float posY_2, int& buttonColor)
{
    if (mouseX >= posX_1 && mouseX <= posX_2 && mouseY >= posY_1 && mouseY <= posY_2)
    {
        buttonColor = buttonOnMouseColor;

        if (GetMouseInput() & MOUSE_INPUT_LEFT)
        {
            return (tutorial == Tutorial::Title) ? true : mouseIntervalTimer <= 0 ? true : false;
        }
    }
    else
    {
        buttonColor = buttonNormalColor;
        return false;
    }
}

void TitleScene::TitleRender() const
{
    DxPlus::Sprite::Draw(backGroundHandle);

    DxPlus::Text::DrawString(L"Tower Defense",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.35f },
        black, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 4,4 }, 0, fontHandle);

    DrawBox
    (
        titlePosX_1, titlePosY_1,
        titlePosX_2, titlePosY_2,
        titleButtonColor,
        true
    );

    DxPlus::Text::DrawString(L"Game Start",
        { text_StartX, text_StartY },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);


    DrawBox
    (
        tutorialPosX_1, tutorialPosY_1,
        tutorialPosX_2, tutorialPosY_2,
        tutorialButtonColor,
        true
    );

    DxPlus::Text::DrawString(L"Tutorial",
        { text_TutorialX, text_TutorialY },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0, fontHandle);
}

void TitleScene::TutorialPurposeRender() const
{
    DxPlus::Sprite::Draw(tutorial_PurposeHandle);

    DxPlus::Text::DrawString(L"迫りくる敵から塔を守れ！！！",
        { DxPlus::CLIENT_WIDTH * 0.5f, 100 },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 3,3 }, 0);
}

void TitleScene::TutorialOperation() const
{
    DxPlus::Text::DrawString(L"移動：WASD　ダッシュ：左Shift　ジャンプ：Space\n\n射撃：左クリック　リロード：R　武器切り替え：マウスホイール",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.35f },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2,2 }, 0);
}

void TitleScene::TutorialTurretRelease() const
{
    DxPlus::Sprite::Draw(tutorial_TurretReleaseHandle);

    DxPlus::Text::DrawString(L"敵を倒すとお金が手に入る。\n手に入ったお金でタレットを修理しよう！！！",
        { DxPlus::CLIENT_WIDTH * 0.5f, 100 },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 3,3 }, 0);
}

void TitleScene::TutorialTurretUpgrade() const
{
    DxPlus::Sprite::Draw(tutorial_TurretUpgradeHandle);

    DxPlus::Text::DrawString(L"修理したタレットは\nコインを使って強化することもできる。",
        { DxPlus::CLIENT_WIDTH * 0.5f, 100 },
        textColor, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 3,3 }, 0);
}
