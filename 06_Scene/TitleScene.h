#pragma once
#include "Scene.h"
#include "../01_Core/GameContext.h"

class TitleScene final : public Scene
{
public:
    explicit TitleScene(GameContext* context) : Scene(context) {}
    void Init() override;
    void Update(float deltaTime) override;
    void Render() const override;

private:
    int fontHandle{ -1 };
    int backGroundHandle{ -1 };

    float sizeX{ 200 };
    float sizeY{ 50 };
    float posX_1{ DxPlus::CLIENT_WIDTH * 0.5f  - sizeX };
    float posX_2{ DxPlus::CLIENT_WIDTH * 0.5f  + sizeX };
    float posY_1{ DxPlus::CLIENT_HEIGHT * 0.75f - sizeY };
    float pos_Y2{ DxPlus::CLIENT_HEIGHT * 0.75f + sizeY };
    float text_StartX{ posX_1 + sizeX };
    float text_StartY{ posY_1 + sizeY };

    const int buttonNormalColor = DxLib::GetColor(0, 0, 0);
    const int buttonOnMouseColor = DxLib::GetColor(255, 255, 255);
    int buttonColor = DxLib::GetColor(0, 0, 0);

    const int black = DxLib::GetColor(0, 0, 0);
};
