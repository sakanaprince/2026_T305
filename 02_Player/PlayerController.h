#pragma once
#include "../DxPlus/DxPlus.h"
#include "CameraController.h"
#include "Gun.h"
#include "Bullet.h"
#include "../05_Stage/Stage.h"
#include "../07_Math/Vector3.h"
#include "../10_Physics/Collision.h"
#include "../99_Utility/Const.h"

class PlayerController
{
public:
	void SetBulletPointer(Bullet* b, int count) {
		bullets = b;
		bulletCount = count;
	}

	const Collision::Sphere GetPlayerSphere() const {
		Collision::Sphere s{};
		s.centerPos = position;
		s.radius = Const::PLAYER_ENEMY_RADIUS;
		return s;
	}

	//プレイヤーの位置を取得
	const Vec3& GetPosition() const { return position; }
	const Vec3& GetCameraForward() const { return camera.GetForward(); }
	//プレイヤーの生存を取得
	const bool IsAlive() const { return isAlive; }
	bool IsGrounded() const { return isGrounded; }
	void SetPrevMouse(int mouseX, int mouseY) { prevMouse = { mouseX, mouseY }; }
	//プレイヤーのHPを取得
	const int GetHp() const { return hp; }

	void Init();
	void Reset();
	void Update(float deltaTime, Stage& stage);
	void Step(float deltaTime, Stage& stage, const Vec3& moveVec);
	void Draw() const;
	void DrawHpBar() const;

	//ダメージを渡してその分をHPから引く
	void TakeDamage(const int damage);
	void FireBullet(const Vec3& eye, const Vec3& forward);
	Vec3 RandomSpreadDirection(const Vec3& forward, float spreadDeg);

private:
	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	Vec3 forward{ 0.0f,0.0f,0.0f };
	Vec3 right{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	float pitch{ 0.0f };

	bool isAlive{ true };
	bool isGrounded{ true };
	bool isAim{ false };
	bool isReload{ false };

	int hp{ 0 };
	int jumpCount{ 0 };

	int bulletCount{ 0 };

	int currentGunType{ 0 };
	int pistolAmmo{ 0 };
	int rifleAmmo{ 0 };
	int shotgunAmmo{ 0 };

	float invincibleTimer{ 0.0f };
	float damageTimer{ 0.0f };
	float respawnTimer{ 0.0f };
	float fireTimer{ 0.0f };
	float fireInterval{ 0.0f };
	float reloadTimer{ 0.0f };

	int deadFont{ -1 };
	int gunFont{ -1 };
	int reloadFont{ -1 };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	CameraController camera;
	Gun gun;
	Bullet* bullets = nullptr;
};
