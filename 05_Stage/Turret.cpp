#include "Turret.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"
#include "../08_Debug/DebugUI.h"
#include "../99_Utility/Const.h"

void Turret::Init()
{
	modelBrokenTurret = RM().GetModel(ResourceKeys::Model_BrokenTurret);
	modelTurret = RM().GetModel(ResourceKeys::Model_Turret);
	modelTurretHandle = modelBrokenTurret;
	MV1SetScale(modelTurretHandle, DxConv::ToVECTOR(scale));
}

void Turret::Reset(Vec3 startPosition)
{
	position = startPosition;
	scale = { 0.5f,0.5f,0.5f };
	yaw = 0.0f;
	state = State::Broken;
}

void Turret::Update(float deltaTime, PlayerController& player)
{
	switch (state)
	{
	case Broken:
		BrokenUpdate(player);
		break;
	case Available:
		AvailableUpdate(deltaTime, player);
		break;
	default:
		break;
	}
}

void Turret::BrokenUpdate(PlayerController& player)
{
	//Vec3 toPlayer = player.GetPos() - position;
	//float dir = toPlayer.Length();

	////距離が一定以下の時に0を押すと解放できる
	//if (dir <= Const::TULLET_RELEASEDISTANCE && CheckHitKey(KEY_INPUT_0))
	//{
	//	//モデルの切り替え
	//	modelTurretHandle = modelTurret;
	//	state = State::Available;
	//}
}

void Turret::AvailableUpdate(float deltaTime, PlayerController player)
{
	//仮でプレイヤーのいる方向に向くようになってます
	//Vec3 toPlayer = player.GetPos() - position;
	//toPlayer.y = 0;
	//toPlayer = toPlayer.Normalized();
	//yaw = std::atan2(toPlayer.x, toPlayer.z);
}


void Turret::Draw() const
{
	if (modelTurretHandle < 0) { return; }

	MV1SetPosition(modelTurretHandle, DxConv::ToVECTOR(position));
	MV1SetRotationXYZ(modelTurretHandle, DxConv::ToVECTOR({ 0.0f, yaw, 0.0f }));
	MV1DrawModel(modelTurretHandle);
}
