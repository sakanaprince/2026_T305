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
	position = { 100.0f,50.0f,0.0f };
	scale = { 0.0f,0.0f,0.0f };

	currentGunType = { 0 };
}

void Gun::Update(float deltaTime)
{
	//マウスホイールで銃の種類の切り替え
	int wheelRot = GetMouseWheelRotVol();
	currentGunType += wheelRot;
	if (currentGunType < 0) currentGunType = 2;
	if (currentGunType > 2) currentGunType = 0;
}

void Gun::Draw() const
{
	if (pistolModel < 0 || rifleModel < 0 || shotgunModel < 0) return;

	switch (currentGunType)
	{
	case 0:
		MV1SetPosition(pistolModel, DxConv::ToVECTOR(position));
		MV1DrawModel(pistolModel);
		break;
	case 1:
		MV1SetPosition(rifleModel, DxConv::ToVECTOR(position));
		MV1DrawModel(rifleModel);
		break;
	case 2:
		MV1SetPosition(shotgunModel, DxConv::ToVECTOR(position));
		MV1DrawModel(shotgunModel);
		break;
	}
}
