#pragma once
#include "../DxPlus/DxPlus.h"
#include "../05_Stage/Stage.h"
#include "../02_Player/CameraController.h"
#include "../02_Player/PlayerController.h"
#include "../08_Debug/Grid.h"
#include "../01_Core/Entity.h"
#include "../03_Enemy/EnemyLow.h"
#include "../05_Stage/Turret.h"

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
    Turret turret;
    CameraController camera;
    Grid grid;

    std::vector<std::unique_ptr<Entity>> entities;

    static constexpr int TURRET_COUNT = 4;
    Turret turrets[TURRET_COUNT];
};
