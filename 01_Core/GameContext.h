#pragma once
#include "../DxPlus/DxPlus.h"
#include "../05_Stage/Stage.h"
#include "../02_Player/CameraController.h"
#include "../02_Player/PlayerController.h"
#include "../08_Debug/Grid.h"
#include "../03_Enemy/EnemyLow.h"

class GameContext
{
public:
    GameContext() = default;
    ~GameContext() = default;

    void Init();
    void Reset();
    void Update(float deltaTime);
    void Draw() const;

private:
    PlayerController player;
    EnemyLow enemy;
    Stage stage;
    CameraController camera;
    Grid grid;
};
