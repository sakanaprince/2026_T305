#pragma once
#include "../DxPlus/DxPlus.h"
#include "CameraController.h"
#include "Bullet.h"
#include "../05_Stage/Stage.h"
#include "../07_Math/Vector3.h"

class PlayerController
{
public:
	void SetBulletPointer(Bullet* b, int count) {
		bullets = b;
		bulletCount = count;
	}
	const Vec3& GetPosition() const { return position; }

	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;

private:
	Vec3 position{ 0.0f,50.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	Vec3 forward{ 0.0f,0.0f,0.0f };
	Vec3 right{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	float pitch{ 0.0f };
	float radius{ 10.0f };
	bool isGrounded{ true };
	int bulletCount{ 0 };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	CameraController camera;
	Bullet* bullets = nullptr;
	Stage stage;
};

