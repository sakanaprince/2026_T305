#pragma once
#include "../07_Math/Vector3.h"
#include "../02_Player/PlayerController.h"

#include "../05_Stage/EnemyRoot.h"

#include "../10_Physics/Collision.h"

class EnemySpawner;

class Entity
{
public:
    Entity() = default;


    //基底クラスのもんだいが直ったら、initでプレイヤーを受けとる

    //アクセサー
    const Vec3& const GetPosition() { return position; }
    const float GetRadius()const { return radius; }
    const float GetHeight()const { return height; }
    const Collision::Sphere GetSphere() { return { position, radius }; }
    const bool IsAlive()const { return isAlive; }

    void SetPosition(const Vec3& pos) { position = pos; }

    /// <summary>
    /// GameContextで紐づけてもらう
    /// </summary>
    void BindEnemySpawner(EnemySpawner* enSpawner) { pEnemySpawner = enSpawner; }


    //＝＝＝＝おそらく敵しか使わないもの＝＝＝＝＝＝＝
    void SetEnemyRoot_pointer(EnemyRoot* enRoot) { pEnemyRoot = enRoot; }
    void SetPlayerPointer(PlayerController* pc) { playerCont = pc; };
    void Kill(){ isAlive = false; }
    //＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    
    //アクセサー

    //ほんとは純粋仮想関数にしたいけど、配列を作る時にエラーが
    virtual void Init(EnemyRoot* enRoot) {};
    virtual void Reset() { MessageBox(NULL, L"なぜ基底クラスのResetを呼ぶのか", L"", FALSE); };
    virtual void Update(float deltaTime) { MessageBox(NULL, L"なぜ基底クラスのUpdateを呼ぶのか", L"", FALSE); };
    virtual void Draw()const {};
    virtual void DrawDebug()const {}; //判定の可視化とか で
    virtual void Release() {}; 



    virtual void TakeDamage(int amount) {};

protected:
    int currentHp;
    Vec3 position;
    Vec3 velocity;
    Vec3 scale;
    float yaw; //向いてる方向
    bool isMoving{ false };
    bool isAlive{ false };

    float moveSpeed{ 80.0f };

    Vec3 moveDir{ 0.0f, 0.0f, 0.0f };

    float radius{ 60.0f };
    float height{ 100.0f };

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

    virtual void StepGround(float deltaTime) ;

    //ポインターまとめ
    PlayerController* playerCont{ nullptr };
    EnemySpawner* pEnemySpawner{ nullptr };
    EnemyRoot* pEnemyRoot{nullptr};



    //＝＝＝＝おそらく敵しか使わないもの＝＝＝＝＝＝＝
    Vec3 rootTargetPoint{ 0.0f, 0.0f, 0.0f };
    size_t rootTargetIndex{ 0 };

    virtual void BodyLine()const {};
    float animTimer{ 0.0f };

    const float  ROOTPOINT_DISTANCE_LIMIT{ 10.0f };

    float damageReactionTimer{ 0.0f };
    const float DAMAGE_REACTION_TIME{ 0.08f };
    bool isDamageReaction{ false };

    float killedReactionTimer{ 0.0f };
    const float KILLED_REACTION_TIME{ 0.2f };
    bool isKilledReaction{ false };
    //＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
};

