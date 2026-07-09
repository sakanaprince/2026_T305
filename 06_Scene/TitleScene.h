#pragma once
#include "Scene.h"
#include "../01_Core/GameContext.h"

enum Tutorial
{
    Title,           //タイトル画面
    Purpose,         //目的
    Operation,       //操作
    Turret_Release,  //タレットの解放
    Turret_Upgrade,  //タレットのアップグレード
    Shop,            //ショップのチュートリアル
    None             //これ以上チュートリアルはない
};

class TitleScene final : public Scene
{
public:
    explicit TitleScene(GameContext* context) : Scene(context) {}
    void Init() override;
    void Update(float deltaTime) override;
    void Render() const override;

    bool ButtonCheckHit(int mouseX, int mouseY, float posX_1, float posX_2, float posY_1, float posY_2, int& buttonColor);

    void TitleRender() const;
    void TutorialPurposeRender() const;
    void TutorialOperation() const;
    void TutorialTurretRelease() const;
    void TutorialTurretUpgrade() const;
    void TutorialShop() const;

private:
    int fontHandle{ -1 };
    int backGroundHandle{ -1 };
    int tutorial_PurposeHandle{ -1 };
    int tutorial_TurretReleaseHandle{ -1 };
    int tutorial_TurretUpgradeHandle{ -1 };
    int tutorial_ShopHandle{ -1 };
    int bgmHandle{ -1 };

    int titleButtonSizeX{ 200 };
    int titleButtonSizeY{ 50 };

    //タイトルボタンの設定
    float titlePosX_1{ DxPlus::CLIENT_WIDTH * 0.5f  - titleButtonSizeX };
    float titlePosX_2{ DxPlus::CLIENT_WIDTH * 0.5f  + titleButtonSizeX };
    float titlePosY_1{ DxPlus::CLIENT_HEIGHT * 0.55f - titleButtonSizeY };
    float titlePosY_2{ DxPlus::CLIENT_HEIGHT * 0.55f + titleButtonSizeY };
    float text_StartX{ titlePosX_1 + titleButtonSizeX };
    float text_StartY{ titlePosY_1 + titleButtonSizeY };

    //チュートリアルボタンの設定
    float tutorialPosX_1{ DxPlus::CLIENT_WIDTH * 0.5f - titleButtonSizeX };
    float tutorialPosX_2{ DxPlus::CLIENT_WIDTH * 0.5f + titleButtonSizeX };
    float tutorialPosY_1{ DxPlus::CLIENT_HEIGHT * 0.75f - titleButtonSizeY };
    float tutorialPosY_2{ DxPlus::CLIENT_HEIGHT * 0.75f + titleButtonSizeY };
    float text_TutorialX{ tutorialPosX_1 + titleButtonSizeX };
    float text_TutorialY{ tutorialPosY_1 + titleButtonSizeY };

    float nextAndReturnButtonSizeX{ 200 };
    float nextAndReturnButtonSizeY{ 50 };
    float nextPosX_1{ DxPlus::CLIENT_WIDTH * 0.9f - nextAndReturnButtonSizeX };
    float nextPosX_2{ DxPlus::CLIENT_WIDTH * 0.9f + nextAndReturnButtonSizeX };
    float nextPosY_1{ DxPlus::CLIENT_HEIGHT * 0.9f - nextAndReturnButtonSizeY };
    float nextPosY_2{ DxPlus::CLIENT_HEIGHT * 0.9f + nextAndReturnButtonSizeY };
    float text_NextX{ nextPosX_1 + nextAndReturnButtonSizeX };
    float text_NextY{ nextPosY_1 + nextAndReturnButtonSizeY };

    float returnPosX_1{ DxPlus::CLIENT_WIDTH * 0.1f - nextAndReturnButtonSizeX };
    float returnPosX_2{ DxPlus::CLIENT_WIDTH * 0.1f + nextAndReturnButtonSizeX };
    float returnPosY_1{ DxPlus::CLIENT_HEIGHT * 0.9f - nextAndReturnButtonSizeY };
    float returnPosY_2{ DxPlus::CLIENT_HEIGHT * 0.9f + nextAndReturnButtonSizeY };
    float text_returnX{ returnPosX_1 + nextAndReturnButtonSizeX };
    float text_returnY{ returnPosY_1 + nextAndReturnButtonSizeY };

    const int buttonNormalColor = DxLib::GetColor(0, 0, 0);
    const int buttonOnMouseColor = DxLib::GetColor(255, 255, 255);
    int titleButtonColor = DxLib::GetColor(0, 0, 0);
    int tutorialButtonColor = DxLib::GetColor(0, 0, 0);
    int nextButtonColor = GetColor(0, 0, 0);
    int returnButtonColor = GetColor(0, 0, 0);

    const int black = DxLib::GetColor(0, 0, 0);

    int tutorial{ 0 };

    //マウスが連続で反応しないようにする
    float mouseInterval{ 1.0f };
    float mouseIntervalTimer{ 0 };
};
