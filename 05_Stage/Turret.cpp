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
	MV1SetScale(modelBrokenTurret, DxConv::ToVECTOR(scale));
	MV1SetScale(modelTurret, DxConv::ToVECTOR(scale));
	modelTurretHandle = modelBrokenTurret;


	for (auto& a : arrow)
	{
		a.Init();
	}
}

void Turret::Reset(Vec3 startPosition)
{
	position = startPosition;
	scale = { 1.0f,1.0f,1.0f };
	yaw = 0.0f;
	state = State::Broken;

	for (auto& a : arrow)
	{
		a.Reset();
	}
}

void Turret::Update(float deltaTime, PlayerController& player, EnemyLow& enemy)
{
	switch (state)
	{
	case Broken:
		BrokenUpdate(player);
		break;
	case Available:
		AvailableUpdate(deltaTime, enemy);
		break;
	default:
		break;
	}
}

void Turret::BrokenUpdate(PlayerController& player)
{
	Vec3 toPlayer = player.GetPosition() - position;
	float dir = toPlayer.Length();
	if (dir <= Const::TULLET_RELEASEDISTANCE && CheckHitKey(KEY_INPUT_0))
	{
		modelTurretHandle = modelTurret;
		state = State::Available;
	}
}

void Turret::AvailableUpdate(float deltaTime, EnemyLow enemy)
{	
	for (auto& a : arrow)
	{
		if (!a.IsActive()) { continue; }

		a.Update(deltaTime);
	}

	Vec3 toPlayer = enemy.GetPosition() - position;

	float dirX = toPlayer.LengthIndividual(toPlayer.x);
	float dirZ = toPlayer.LengthIndividual(toPlayer.z);

	if (dirX > Const::TULLET_SHOTRANGE || dirZ > Const::TULLET_SHOTRANGE) { return; }
    shotIntervalTimer -= deltaTime;
	
	toPlayer = toPlayer.Normalized();
	yaw = std::atan2(toPlayer.x, toPlayer.z);
	
	if (shotIntervalTimer <= 0.0f)
	{
		for (auto& a : arrow)
		{
			if (a.IsActive()) { continue; }

			a.LaunchArrow(toPlayer, deltaTime, *this);
			Debug().Log(u8"–î‚ª”­ŽË‚³‚ê‚½");
			break;
		}
		shotIntervalTimer = shotIntervalTime;
	}
}


void Turret::Draw() const
{
	if (modelTurretHandle < 0) { return; }

	MV1SetPosition(modelTurretHandle, DxConv::ToVECTOR(position));
	MV1SetRotationXYZ(modelTurretHandle, DxConv::ToVECTOR({ 0.0f, yaw, 0.0f }));
	MV1DrawModel(modelTurretHandle);

	for (auto& a : arrow)
	{
		if (!a.IsActive()) { continue; }

		a.Draw();
	}
}
