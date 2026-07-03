#pragma once
#include "../07_Math/Vector3.h"
#include "../02_Player/PlayerController.h"

#include "../05_Stage/EnemyRoot.h"

#include "../10_Physics/Collision.h"

#include "../09_Effect/Explosion.h"

class EnemySpawner;
class Player;

class Entity
{
public:
    Entity() = default;


    //基底クラスのもんだいが直ったら、initでプレイヤーを受けとる

    //アクセサー
    const Vec3& const GetPosition() { return position; }
    const float GetRadius()const { return radius; }
    const float GetHeight()const { return height; }
    const Collision::Sphere GetSphere() const { return { {position.x, position.y + skin, position.z}, hitSphereRadius }; }
    const bool IsAlive()const { return isAlive; }

    void SetPosition(const Vec3& pos) { position = pos; }

    /// <summary>
    /// GameContextで紐づけてもらう
    /// </summary>
    void BindEnemySpawner(EnemySpawner* enSpawner) { pEnemySpawner = enSpawner; }


    //＝＝＝＝おそらく敵しか使わないもの＝＝＝＝＝＝＝
    void SetEnemyRoot_pointer(EnemyRoot* enRoot) { pEnemyRoot = enRoot; }
    void SetPlayerPointer(PlayerController* pc) { pPlayer = pc; };
    void Kill(){ isAlive = false; }
    //＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    
    //アクセサー

    //ライフサイクル
    //ほんとは純粋仮想関数にしたいけど、配列を作る時にエラーが...え？直った。vectorにしたからかな
    virtual void Init(EnemyRoot* enRoot, PlayerController* pc) = 0;
    virtual void Reset() { MessageBox(NULL, L"なぜ基底クラスのResetを呼ぶのか", L"", FALSE); };
    virtual void Update(float deltaTime) { MessageBox(NULL, L"なぜ基底クラスのUpdateを呼ぶのか", L"", FALSE); };
    virtual void Draw()const;
    virtual void DrawDebug()const {}; //判定の可視化とか で
    virtual void Release() {}; 


    virtual void TakeDamage(int amount);
 

protected:
    //HP関連
    int initHp;
    int currentHp;
    const float hpBarHeight{ 20 };

    Vec3 position;
    Vec3 velocity;
    Vec3 scale;
    float yaw; //向いてる方向
    bool isMoving{ false };
    bool isAlive{ false };

    float moveSpeed{ 80.0f };

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

    //ポインターまとめ
    PlayerController* pPlayer{ nullptr };
    EnemySpawner* pEnemySpawner{ nullptr };
    EnemyRoot* pEnemyRoot{nullptr};

    Explosion explosion;

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

