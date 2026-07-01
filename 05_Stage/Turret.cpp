#include "Turret.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"
#include "../08_Debug/DebugUI.h"
#include "../99_Utility/Const.h"

void Turret::Init(PlayerController* _player, EnemySpawner* _enemySpawner, Coin* _coin)
{
	modelBrokenTurret = RM().GetModel(ResourceKeys::Model_BrokenTurret);
	modelTurret = RM().GetModel(ResourceKeys::Model_Turret);
	MV1SetScale(modelBrokenTurret, DxConv::ToVECTOR(scale));
	MV1SetScale(modelTurret, DxConv::ToVECTOR(scale));
	modelTurretHandle = modelBrokenTurret;

	player = _player;
	enemySpawner = _enemySpawner;
	coin   = _coin;

	for (auto& a : arrows)
	{
		a.Init();
	}

	spritePrice = RM().GetSprite(ResourceKeys::Sprite_TurretPrice);
}

void Turret::Reset(Vec3 startPosition)
{
	position = startPosition;
	scale = { 1.0f,1.0f,1.0f };
	yaw = 0.0f;
	state = State::Broken;
	isPriceDraw = false;

	for (auto& a : arrows)
	{
		a.Reset();
	}
}

void Turret::Update(float deltaTime)
{
	switch (state)
	{
	case Broken:
		BrokenUpdate();
		break;
	case Available:
		AvailableUpdate(deltaTime);
		break;
	default:
		break;
	}
}

void Turret::BrokenUpdate()
{
	Vec3 toPlayer = player->GetPosition() - position;
	float dir = toPlayer.Length();
	if (dir <= Const::TULLET_RELEASEDISTANCE)
	{
		isPriceDraw = true;

		if (CheckHitKey(KEY_INPUT_0) && coin->GetCoin() >= turretCoin)
		{
			coin->MinusCoin(turretCoin);
			modelTurretHandle = modelTurret;
			state = State::Available;
			isPriceDraw = false;
		}
	}
	else
	{
		isPriceDraw = false;
	}
}

void Turret::AvailableUpdate(float deltaTime)
{	
	for (auto& a : arrows)
	{
		if (!a.IsActive()) { continue; }

		a.Update(deltaTime);
	}

	Vec3 toEnemy = GetNearbyEnemy();

	if (toEnemy.Length() <= 0) { return; }

	toEnemy = toEnemy.Normalized();
	yaw = std::atan2(toEnemy.x, toEnemy.z);

    shotIntervalTimer -= deltaTime;
	
	if (shotIntervalTimer <= 0.0f)
	{
		for (auto& a : arrows)
		{
			if (a.IsActive()) { continue; }

			a.LaunchArrow(toEnemy, deltaTime, *this);
			Debug().Log(u8"矢が発射された");
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

	for (auto& a : arrows)
	{
		if (!a.IsActive()) { continue; }

		a.Draw();
	}

	if (isPriceDraw)
	{
		DrawRotaGraph3D(position.x, position.y + 70, position.z, 0.05, 0, spritePrice, true);
	}
}

Vec3 Turret::GetNearbyEnemy()
{
	float minDir = std::numeric_limits<float>::infinity();
	Vec3 targetEnemy = { 0.0f,0.0f,0.0f };

	for (int i = 0; i < Const::MAX_ENEMY_COUNT; i++)
	{
		EnemyLow enemy = enemySpawner->GetEnemy(i);

		if (!enemy.IsAlive()) { continue; }

		Vec3 toEnemy = enemy.GetPosition() - position;

		//XとZの距離を個別で取得
		float dirX = toEnemy.LengthIndividual(toEnemy.x);
		float dirZ = toEnemy.LengthIndividual(toEnemy.z);

		//XとZどちらかが遠い場合はターゲットにしない
		if (dirX > Const::TULLET_SHOTRANGE || dirZ > Const::TULLET_SHOTRANGE) { continue; }

		float length = toEnemy.Length();
		if (length <= minDir)
		{
			targetEnemy = toEnemy;
			minDir = length;
		}
	}

	return targetEnemy;
}
