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
#include "../05_Stage/Core.h"

#include <string>

class GameContext
{
public:
    GameContext() = default;
    ~GameContext() = default;

    void Init();
    void Reset();
    void Update(float deltaTime);
    void Draw() const;

    float GetLimit_Timer() { return limit_Timer; }

    Core& GetCore() { return core; }
    const Core& GetCore() const { return core; }

    Coin& GetCoinManager() { return coin; }
    const Coin& GetCoinManager() const { return coin; }

private:
    void TimeLimit(float deltaTime);
    void CollisionEnemyBullet();
    void CollisionEnemyArrow();

    PlayerController player;
    EnemyRoot enemyRoot;
    EnemySpawner enemySpawner;
    Stage stage;
    CameraController camera;
    Bullet bullets[Const::AMMO_MAX];
    Grid grid;
    Coin coin;
    Core core;

    std::vector<std::unique_ptr<Entity>> entities;

    class Turret turrets[Const::TURRET_COUNT];

    //Žc‚èŽžŠÔŒv‘ª—p
    float limit_Timer{ 0 };
    float limit_Time{ 300 };
    float limit_prevTime{ 0 };

    int fontHandle{ -1 };
    std::wstring text_Timer;
};
