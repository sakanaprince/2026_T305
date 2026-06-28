#pragma once
#include "../DxPlus/DxPlus.h"
#include "../01_Core/Entity.h"
#include "../02_Player/CameraController.h"
#include "../02_Player/Bullet.h"
#include "../02_Player/Coin.h"
#include "../03_Enemy/EnemyLow.h"
#include "../03_Enemy/EnemySpawner.h"
#include "../05_Stage/Stage.h"
#include "../05_Stage/Turret.h"
#include "../05_Stage/EnemyRoot.h"
#include "../08_Debug/Grid.h"
#include "../99_Utility/Const.h"

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
    EnemyRoot enemyRoot;

    //1_EnemySpawnerを追加してほしい
    //2_そのスポナーに対してInit Update Draw を3つ、contextで呼んでほしい
    EnemySpawner enemySpawner;


    Stage stage;
    Turret turret;
    CameraController camera;
    Bullet bullets[Const::BULLET_COUNT];
    Grid grid;
    Coin coin;

    std::vector<std::unique_ptr<Entity>> entities;

    Turret turrets[Const::TURRET_COUNT];
};
