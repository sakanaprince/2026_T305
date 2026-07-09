#pragma once
#include "../DxPlus/DxPlus.h"
#include "../01_Core/Entity.h"
#include "../01_Core/EnemyDataMaster.h"
#include "../02_Player/CameraController.h"
#include "../02_Player/Bullet.h"
#include "../02_Player/Coin.h"
#include "../03_Enemy/EnemyLow.h"
#include "../03_Enemy/EnemySpawner.h"
#include "../05_Stage/Stage.h"
#include "../05_Stage/Turret.h"
#include "../05_Stage/EnemyRoot.h"
#include "../05_Stage/Core.h"
#include "../08_Debug/Grid.h"
#include "../11_Shop/ShopManager.h"
#include "../12_Sound/SoundManager.h"
#include "../99_Utility/Const.h"


#include <string>
#include "../11_Shop/Trap.h"

class GameContext
{
public:
    GameContext(SoundManager& _sound) : soundManager(_sound){}
    ~GameContext() = default;

    void Init();
    void Reset();
    void Update(float deltaTime);
    void Draw() const;

    float GetLimit_Timer() { return limit_Timer; }

    PlayerController& GetPlayer() { return player; }
    const PlayerController& GetPlayer() const { return player; }

    Core& GetCore() { return core; }
    const Core& GetCore() const { return core; }

    Coin& GetCoinManager() { return coin; }
    const Coin& GetCoinManager() const { return coin; }

    EnemySpawner& GetEnemySpawner() { return enemySpawner; }
    const EnemySpawner& GetEnemySpawner() const { return enemySpawner; }

    SoundManager& GetSoundManager() { return soundManager; }
    const SoundManager& GetSoundManager() const { return soundManager; }

    int GetTrapCount() const { return possessionTrap; }

    void UnlockMap() { unlockMap = true; }

    //トラップを購入したときの処理
    void BuyTrap() { possessionTrap++; }

private:
    void MouseController();
    void TimeLimit(float deltaTime);
    void CollisionEnemyBullet();
    void CollisionEnemyArrow();
    void CollisionEnemyTrap();
    //トラップの設置
    void InstallationTrap();

    PlayerController player;
    EnemyRoot enemyRoot;
    EnemySpawner enemySpawner;
    Stage stage;
    CameraController camera;
    Bullet bullets[Const::AMMO_MAX];
    Grid grid;
    Coin coin;
    Core core;
    ShopManager shopManager;
    EnemyDataMaster enemyDataManster;

    SoundManager& soundManager;

    Turret turrets[Const::TURRET_COUNT];

    bool unlockMap{ false };

    //残り時間計測用
    float limit_Timer{ 0 };
    float limit_Time{ 300 };
    float limit_prevTime{ 0 };

    int fontHandle{ -1 };
    std::wstring text_Timer;

    int trapModelHandle{ -1 };  //罠のモデル
    std::vector<std::unique_ptr<Trap>> spawnTraps;  //設置している罠
    int possessionTrap{ 0 };  //現在所持している罠の数

    bool shopOpen{ false };
    int E_KEY_prevFrameDown{ -1 };

    int soundSetTrapHandle{ -1 };
    std::wstring textTrapCount{L"" };
};
