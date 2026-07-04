#include "Gun.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"

void Gun::Init()
{
	pistolModel = RM().GetModel(ResourceKeys::Model_Pistol);
	rifleModel = RM().GetModel(ResourceKeys::Model_Rifle);
	shotgunModel = RM().GetModel(ResourceKeys::Model_Shotgun);
}

void Gun::Reset()
{
	position = { 0.0f,0.0f,0.0f };
	scale = { 0.0f,0.0f,0.0f };
	angle = { 0.0f,0.0f,0.0f };

	currentGunType = { 0 };
}

void Gun::Update(bool isReload)
{
	if (isReload) return;

	//マウスホイールで銃の種類の切り替え
	int wheelRot = GetMouseWheelRotVol();
	currentGunType += wheelRot;
	if (currentGunType < 0) currentGunType = 2;
	if (currentGunType > 2) currentGunType = 0;

	switch (currentGunType)
	{
	case GunType::Pistol:
		ModelHandle = pistolModel;
		forwardNum = 130.0f;
		muzzleNum = 100.0f;
		break;
	case GunType::Rifle:
		ModelHandle = rifleModel;
		forwardNum = 150.0f;
		muzzleNum = 100.0f;
		break;
	case GunType::Shotgun:
		ModelHandle = shotgunModel;
		forwardNum = 150.0f;
		muzzleNum = 100.0f;
		break;
	}
}

void Gun::UpdateFromCamera(const Vec3& playerPos, const Vec3& forward, const Vec3& right, 
	const Vec3& up, bool isAim)
{
	float rightPos = isAim ? 0.0f : 80.0f;
	float upPos = isAim ? 80.0f : 60.0f;

	Vec3 offset = forward * forwardNum + right * rightPos + up * upPos;
	Vec3 muzzlePos = { 0,0,0 };

	position = playerPos + offset;

	// 位置＋回転の行列を作る
	MATRIX mat = MGetIdent();

	// 回転
	mat.m[0][0] = right.x;   mat.m[0][1] = right.y;   mat.m[0][2] = right.z;
	mat.m[1][0] = up.x;      mat.m[1][1] = up.y;      mat.m[1][2] = up.z;
	mat.m[2][0] = forward.x; mat.m[2][1] = forward.y; mat.m[2][2] = forward.z;

	// 位置
	mat.m[3][0] = position.x;
	mat.m[3][1] = position.y;
	mat.m[3][2] = position.z;

	// モデルに適用
	MV1SetMatrix(ModelHandle, mat);
}

void Gun::Draw() const
{
	if (ModelHandle < 0) return;

	MV1DrawModel(ModelHandle);
}
