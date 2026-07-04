#pragma once
#include "../07_Math/Vector3.h"

enum GunType {
	Pistol,
	Rifle,
	Shotgun,
};

class Gun
{
public:
	//Œ»İ‚Ìe‚Ìí—Ş‚ğæ“¾
	const int GetGunType() const { return currentGunType; }

	void Init();
	void Reset();
	void Update(bool isReload);
	void UpdateFromCamera(const Vec3& camPos, const Vec3& forward, const Vec3& right,
		const Vec3& up, bool isAim);
	void Draw() const;

private:
	Vec3 position{ 0,0,0 };
	Vec3 scale{ 0,0,0 };
	Vec3 angle{ 0,0,0 };

	float forwardNum{ 0.0f };
	float muzzleNum{ 0.0f };

	int currentGunType{ 0 };

	int ModelHandle{ -1 };
	int pistolModel{ -1 };
	int rifleModel{ -1 };
	int shotgunModel{ -1 };
};
