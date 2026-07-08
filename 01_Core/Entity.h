#pragma once
#include "../07_Math/Vector3.h"
#include "../02_Player/PlayerController.h"
#include "../05_Stage/EnemyRoot.h"
#include "../10_Physics/Collision.h"
#include "../09_Effect/Explosion.h"
#include "../01_Core/EnemyDataMaster.h"

class EnemySpawner;

class Player;

class Entity
{
public:

    Entity() = default;

    //アクセサー
    void SetPosition(const Vec3& pos) { position = pos; }
    const Vec3& const GetPosition() { return position; }
    const float GetRadius()const { return radius; }
    const float GetHeight()const { return height; }
    const Collision::Sphere GetSphere() const { return { {position.x, position.y + skin, position.z}, hitSphereRadius }; }
    const bool IsAlive()const { return isAlive; }


    /// <summary>
    /// GameContextで紐づけてもらう
    /// </summary>
    void BindEnemySpawner(EnemySpawner* enSpawner) { pEnemySpawner = enSpawner; }

    //アクセサー
    void Kill(){ isAlive = false; }


    //ライフサイクル
    //ほんとは純粋仮想関数にしたいけど、配列を作る時にエラーが...え？直った。vectorにしたからかな
    virtual void Init(EnemyRoot* enRoot, PlayerController* pc, EnemyKey key);
    virtual void Reset() {};
    virtual void Update(float deltaTime);
    virtual void Draw()const;
    virtual void DrawDebug()const {}; //判定の可視化とか で
    virtual void Release() {}; 

    virtual void TakeDamage(int amount);
    virtual void TakeGroundDamage(int amount);

    void BindEnemyDataMaster(EnemyDataMaster* dtm) { pEnemyDataMaster = dtm; }

protected:
    //HP関連
    EnemyKey myKey{EnemyKey::Low};

    int currentHp{1};
    const float hpBarHeight{ 20 };

    //Jsonで調整する
    int initHp{ 30 };
    int coreDamage{ 10 };
    int dropCoin{ 10 };
    float moveSpeed{ 80.0f };

    const float  ROOTPOINT_DISTANCE_LIMIT{ 10.0f };
    Vec3 position;
    Vec3 velocity;
    Vec3 scale;
    float yaw{ 0 }; //向いてる方向
    bool isMoving{ false };
    bool isAlive{ false };
    bool isChasePlayer{ false };
    const float ChaseStartDistance{ 500.0f };


    Vec3 moveDir{ 0.0f, 0.0f, 0.0f };

    float height{ 100.0f };     //高さ、身長
    float radius{ 60.0f };      //半径
    float skin{ 60.0f };        //地面からの浮き上がり

    float hitSphereRadius{ 50.0f };

    void KilledReactionUpdate(float deltaTime)
    {
        if (killedReactionTimer > 0.0f)
        {
            killedReactionTimer -= deltaTime;
            return;
        }

        isAlive = false;
    }

    void DamageReactionUpdate(float deltaTime)
    {
        if (damageReactionTimer > 0.0f)
        {
            damageReactionTimer -= deltaTime;
            return;
        }

        isDamageReaction = false;
    }

    void DrawHpBar() const;

    virtual void StepGround(float deltaTime) ;
    bool IsClosePlayer();
    void SetTargetDirection();

    //ポインターまとめ
    PlayerController* pPlayer{ nullptr };
    EnemySpawner* pEnemySpawner{ nullptr };
    EnemyRoot* pEnemyRoot{nullptr};
    EnemyDataMaster* pEnemyDataMaster{ nullptr };

    Explosion explosion;

  
    Vec3 targetPosition{ 0.0f, 0.0f, 0.0f };
    size_t rootTargetIndex{ 0 };

    virtual void BodyLine()const {};
    float animTimer{ 0.0f };

    float groundDamageInvTimer{ 0.0f };
    const float groundDamageInvTime{ 0.5f };

    //プレイヤーが近くにいたら追いかけ始める
    float startChaseTimer{ 0.0f };
    const float START_CHASE_TIME{ 0.2f };

    //ダメージを受けたときのリアクション用
    float damageReactionTimer{ 0.0f };
    const float DAMAGE_REACTION_TIME{ 0.08f };
    bool isDamageReaction{ false };

    //撃破された時のリアクション用
    float killedReactionTimer{ 0.0f };
    const float KILLED_REACTION_TIME{ 0.2f };
    bool isKilledReaction{ false };
};

