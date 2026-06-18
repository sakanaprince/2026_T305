#pragma once
#include "../07_Math/Vector3.h"

class Entity
{
public:
    Entity() = default;

    //基底クラスのもんだいが直ったら、initでプレイヤーを受けとる

    //アクセサー
    const Vec3& const GetPosition() { return position; }
    const float GetRadius()const { return radius; }
    const float GetHeight()const { return height; }
    void SetPosition(const Vec3& pos) { position = pos; }
    //アクセサー

    virtual void Init() = 0;
    virtual void Reset(const Vec3& startPosition, float startYaw) {};
    virtual void Update(float deltaTime, const Vec3& playerPos) {};
    virtual void Draw()const {};
    virtual void DrawDebug()const {}; //判定の可視化とか で
    virtual void Release() {}; 


protected:
    Vec3 position;
    Vec3 velocity;
    Vec3 scale;
    float yaw; //向いてる方向
    bool isMoving{ false };

    float moveSpeed{ 80.0f };

    Vec3 moveDir{ 0.0f, 0.0f, 0.0f };

    float radius{ 60.0f };
    float height{ 100.0f };
};

