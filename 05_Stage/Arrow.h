#pragma once
#include "../07_Math/Vector3.h"
#include "../05_Stage/Stage.h"
#include "../10_Physics/Collision.h"

class Turret;
class Arrow
{
public:
	Arrow() = default;
	~Arrow() = default;

	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;

	//当たり判定を返す関数
	Collision::Sphere GetSphereArrow() const { return sphereArrow; }

	//矢の発射時の関数
	void LaunchArrow(Vec3 forward, class Turret& turret);

	//矢が使用されているかどうか
	bool IsActive() const { return isActive; }
	void Kill() { isActive = false; }

	//矢のダメージ
	int GetArrowDamage() const { return arrowDamage; }
	void SetArrowDamage(int damage) { arrowDamage = damage; }

private:
	int modelHandle{ -1 };

	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 scale{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float speed{ 5000.0f };
	bool isActive{ false };
	float yaw{ 0.0f };

	float lifeTimer{ 0.0f };
	float lifeTime{ 1.0f };

	int arrowDamage{ 1 };

	Collision::Sphere sphereArrow;
};

