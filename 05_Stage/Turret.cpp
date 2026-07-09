#include "Turret.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"
#include "../08_Debug/DebugUI.h"
#include "../99_Utility/Const.h"


void Turret::Init(PlayerController* _player, EnemySpawner* _enemySpawner, Coin* _coin, SoundManager* _sound)
{
	modelBrokenTurret = RM().GetModel(ResourceKeys::Model_BrokenTurret);
	modelTurret = RM().GetModel(ResourceKeys::Model_Turret);
	MV1SetScale(modelBrokenTurret, DxConv::ToVECTOR(scale));
	MV1SetScale(modelTurret, DxConv::ToVECTOR(scale));
	modelTurretHandle = modelBrokenTurret;
	soundArrowHandle = RM().GetSound(ResourceKeys::Sound_Arrow);
	soundUpgradeHandle = RM().GetSound(ResourceKeys::Sound_Upgrade);

	player = _player;
	enemySpawner = _enemySpawner;
	coin = _coin;
	sound = _sound;

	for (auto& a : arrows)
	{
		a.Init();
	}

	spriteReleasePrice = RM().GetSprite(ResourceKeys::Sprite_TurretReleasePrice);
	spriteUpgradePrice = RM().GetSprite(ResourceKeys::Sprite_TurretUpgradePrice);
	spritePrice = spriteReleasePrice;
}

void Turret::Reset(Vec3 startPosition)
{
	position = startPosition;
	scale = { 1.0f,1.0f,1.0f };
	yaw = 0.0f;
	shotIntervalTime = shotIntervalTime_Max;
	state = State::Broken;
	isPriceDraw = false;
	spritePrice = spriteReleasePrice;
	modelTurretHandle = modelBrokenTurret;

	for (auto& a : arrows)
	{
		a.Reset();
	}
}

void Turret::Update(float deltaTime)
{
	if (contactIntervalTimer > 0)
	{
		contactIntervalTimer -= deltaTime;
	}

	if (state == State::Available) { AvailableUpdate(deltaTime); }

	//プレイヤーとの距離を取得
	Vec3 toPlayer = player->GetPosition() - position;
	float dir = toPlayer.Length();

	//プレイヤーがタレットの接触判定内に入っているどうかを調べる
	if (dir <= Const::TULLET_CONTACTDISTANCE)
	{
		//お金の画像を表示する
		isPriceDraw = true;

		if (!CheckHitKey(KEY_INPUT_RETURN) || contactIntervalTimer > 0) { return; }

		int currentCoin = coin->GetCoin();
		switch (state)
		{
		case Broken:
			if (currentCoin >= turretCoin)
			{
				coin->MinusCoin(turretCoin);
				modelTurretHandle = modelTurret;
				spritePrice = spriteUpgradePrice;
				sound->PlaySENormal(soundUpgradeHandle);
				state = State::Available;
			}
			break;
		case Available:
			if (currentCoin >= turretUpgradeCoin && shotIntervalTime > 0.0f)
			{
				coin->MinusCoin(turretUpgradeCoin);
				shotIntervalTime -= shotIntervalDownRate;
				sound->PlaySENormal(soundUpgradeHandle);
				if (shotIntervalTime <= 0.0f)
				{
					shotIntervalTime = 0.0f;

					//最後まで強化したので画像を消す
					spritePrice = -1;
				}
			}
			break;
		}
		contactIntervalTimer = contactIntervalTime;
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

			a.LaunchArrow(toEnemy, *this);
			sound->PlaySEAtPosition(soundArrowHandle, position);
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
		if (spritePrice < 0) { return; }
		DrawRotaGraph3D(position.x, position.y + 70, position.z, 0.05, 0, spritePrice, true);
	}
}

Vec3 Turret::GetNearbyEnemy()
{
	float minDir = std::numeric_limits<float>::infinity();
	Vec3 targetEnemy = { 0.0f,0.0f,0.0f };

	for (int i = 0; i < enemySpawner->GetEnemyCollectionSize(); i++)
	{
		auto& enemy = enemySpawner->GetEnemy(i);

		if (!enemy->IsAlive()) { continue; }

		Vec3 enemyPos = enemy->GetPosition();
		Vec3 toEnemy = enemyPos - position;

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
