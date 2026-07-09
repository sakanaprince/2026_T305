#pragma once
#pragma once
#include "Scene.h"

class GameClearScene final : public Scene
{
public:
    explicit GameClearScene(class GameContext* context) : Scene(context) {}
    void Init() override;
    void Update(float deltaTime) override;
    void Render() const override;

private:
    int fontHandle{ -1 };
    int backGroundHandle{ -1 };
    int bgmHandle{ -1 };

    float sizeX{ 200 };
    float sizeY{ 50 };

    float titlePosX_1{ DxPlus::CLIENT_WIDTH * 0.5f - sizeX };
    float titlePosX_2{ DxPlus::CLIENT_WIDTH * 0.5f + sizeX };
    float titlePosY_1{ DxPlus::CLIENT_HEIGHT * 0.75f - sizeY };
    float titlePos_Y2{ DxPlus::CLIENT_HEIGHT * 0.75f + sizeY };
    float text_TitleX{ titlePosX_1 + sizeX };
    float text_TitleY{ titlePosY_1 + sizeY };

    const int buttonNormalColor = DxLib::GetColor(0, 0, 0);
    const int buttonOnMouseColor = DxLib::GetColor(255, 255, 255);
    int buttonTitleColor = DxLib::GetColor(0, 0, 0);
    const int black = DxLib::GetColor(0, 0, 0);
};
