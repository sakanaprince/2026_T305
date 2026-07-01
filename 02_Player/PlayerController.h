#pragma once
#include "../DxPlus/DxPlus.h"
#include "CameraController.h"
#include "Bullet.h"
#include "../05_Stage/Stage.h"
#include "../07_Math/Vector3.h"

enum GunType {
	Pistol,
	Rifle,
	Shotgun,
};

class PlayerController
{
public:
	void SetBulletPointer(Bullet* b, int count) {
		bullets = b;
		bulletCount = count;
	}
	//�v���C���[�̈ʒu���擾
	const Vec3& GetPosition() const { return position; }
	//�v���C���[��HP���擾
	const int GetHp() const { return hp; }
	//�_���[�W��n���Ă��̕���HP�������
	void TakeDamage(const int damage) { hp -= damage; }
	//�c�e�����擾
	const int GetAmmoCount() const { return ammoCount; }

	void Init();
	void Reset();
	void Update(float deltaTime, Stage& stage);
	void Step(float deltaTime, const class Stage& stage, const Vec3& moveVec);
	void Draw() const;

private:
	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	Vec3 forward{ 0.0f,0.0f,0.0f };
	Vec3 right{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	float pitch{ 0.0f };

	bool isGrounded{ true };
	bool isReload{ false };

	int hp{ 0 };
	int currentGunType{ 0 };

	int bulletCount{ 0 };
	int ammoCount{ 0 };
	float reloadTimer{ 0.0f };

	int ammoFont{ -1 };
	int gunFont{ -1 };
	int reloadFont{ -1 };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	CameraController camera;
	Bullet* bullets = nullptr;
};
