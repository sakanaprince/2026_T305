#pragma once
#include "Gun.h"
#include "../07_Math/Vector3.h"
#include "../10_Physics/Collision.h"
#include "../99_Utility/Const.h"

class Bullet
{
private:
	Collision::Sphere bullet{};
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float maxLife{ 2.0f };
	float life{ maxLife };
	bool isActive{ false };

	Gun gun;

public:
	const bool IsActive() const { return isActive; }
	void DeActivate() { isActive = false; }
	const Collision::Sphere GetBulletSpere() const { return bullet; }
	const int BulletDamage() const {
		switch (gun.GetGunType())
		{
		case GunType::Pistol:
			return Const::PISTOL_BULLET_DAMAGE;
			break;
		case GunType::Rifle:
			return Const::RIFLE_BULLET_DAMAGE;
			break;
		case GunType::Shotgun:
			return Const::SHOTGUN_BULLET_DAMAGE;
			break;
		}
		return 0;
	}

	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;
	void Fire(const Vec3& pos, const Vec3& dir);
};
