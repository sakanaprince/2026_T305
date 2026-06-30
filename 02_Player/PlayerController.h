#pragma once
#include "../DxPlus/DxPlus.h"
#include "CameraController.h"
#include "Bullet.h"
#include "../05_Stage/Stage.h"
#include "../07_Math/Vector3.h"

struct Capsule {
	Vec3 foot;     // 下側の球の中心
	Vec3 head;     // 上側の球の中心
	float radius;  // カプセルの半径

	Capsule() = default;

	Capsule(const Vec3& pos, float height, float r)
	{
		radius = r;
		foot = pos;
		head = pos + Vec3(0, height, 0);
	}

	void Update(const Vec3& pos, float height)
	{
		foot = pos;
		head = pos + Vec3(0, height, 0);
	}
};

class PlayerController
{
public:
	void SetBulletPointer(Bullet* b, int count) {
		bullets = b;
		bulletCount = count;
	}
	const Vec3& GetPosition() const { return position; }
	const int GetAmmoCount() const { return ammoCount; }

	void Init();
	void Reset();
	void Update(float deltaTime, Stage& stage);
	void Step(float deltaTime, const class Stage& stage);
	void Draw() const;

private:
	Capsule capsule{};

	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	Vec3 forward{ 0.0f,0.0f,0.0f };
	Vec3 right{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	float pitch{ 0.0f };
	bool isGrounded{ true };
	bool isReload{ false };
	int bulletCount{ 0 };
	int ammoCount{ 0 };
	float reloadTimer{ 0.0f };

	int ammoFont{ -1 };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	CameraController camera;
	Bullet* bullets = nullptr;
};
