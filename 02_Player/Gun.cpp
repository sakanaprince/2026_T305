#include "Gun.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"

void Gun::Init()
{
	pistolModel = RM().GetModel(ResourceKeys::Model_Pistol);
}

void Gun::Reset()
{
	position = { 0.0f,0.0f,0.0f };
	scale = { 0.0f,0.0f,0.0f };
}

void Gun::Draw() const
{
	if (pistolModel < 0) return;

	MV1SetPosition(pistolModel, DxConv::ToVECTOR(position));
	MV1DrawModel(pistolModel);
}
