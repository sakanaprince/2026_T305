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

    float posX_1{ DxPlus::CLIENT_WIDTH * 0.5f  - 200 };
    float posX_2{ DxPlus::CLIENT_WIDTH * 0.5f  + 200 };
    float posY_1{ DxPlus::CLIENT_HEIGHT * 0.75f - 50 };
    float pos_Y2{ DxPlus::CLIENT_HEIGHT * 0.75f + 50 };
    const int buttonNormalColor = DxLib::GetColor(0, 0, 0);
    const int buttonOnMouseColor = DxLib::GetColor(255, 255, 255);
    int buttonColor = DxLib::GetColor(0, 0, 0);
};
