#include "Entity.h"
#include "../03_Enemy/EnemySpawner.h"

#include "../04_Resource/ResourceManager.h"
#include "../12_Sound/SoundManager.h"

void Entity::Init(EnemyRoot* enRoot, PlayerController* pc, EnemyKey key)
{
	isAlive = false;
	pEnemyRoot = enRoot;
	pPlayer = pc;
	myKey = key;

	auto data = pEnemyDataMaster->GetEnemyStatus(key);
	initHp = data->maxHp;
	moveSpeed = data->moveSpeed;
	dropCoin = data->dropCoin;
	coreDamage = data->coreDamage;

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"null Ptr enemyRoot_p");
		return;
	}
}

void Entity::Update(float deltaTime)
{
	explosion.Update(deltaTime);

	if (!isAlive) { return; }

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"EnemyRoot Null Ptr by Entity");
		return;
	}

	if (isKilledReaction)
	{
		KilledReactionUpdate(deltaTime);
		return;
	}

	if (groundDamageInvTimer > 0.0f) { groundDamageInvTimer -= deltaTime; }

	if (isDamageReaction)
	{
		DamageReactionUpdate(deltaTime);
		return;
	}

	StepGround(deltaTime);

	animTimer += deltaTime;

	startChaseTimer += deltaTime;
	if (startChaseTimer > START_CHASE_TIME)
	{
		startChaseTimer = 0.0f;
		SetTargetDirection();
	}
}

void Entity::Draw() const
{
	explosion.Draw();

	if (!isAlive) { return; }

	//プレイヤーの視野に入っていないならretrun(軽量化)
	bool isPlayerView = false;
	Vec3 playerPos = position - pPlayer->GetPosition();
	Vec3 playerForward = pPlayer->GetCameraForward();

	float dot_startToTargetVecAndSightVec = Vec3::Dot(playerPos, playerForward);

	float scara_startToTarget = sqrtf(playerPos.x * playerPos.x + playerPos.z * playerPos.z);
	float scara_sight = sqrtf(playerForward.x * playerForward.x + playerForward.z * playerForward.z);

	float digCosSeata = dot_startToTargetVecAndSightVec / (scara_startToTarget * scara_sight);

	const float playerSightAngle = cos(DxPlus::Deg2Rad * 50);


	if (digCosSeata > playerSightAngle) { isPlayerView = true; }

	if (!isPlayerView) { return; }

	BodyLine();
	DrawHpBar();
}

void Entity::TakeDamage(int amount)
{
	if (isKilledReaction) { return; }

	//pEnemySpawner->PlaySoundPos(RM().GetSound(ResourceKeys::Sound_Arrow), position);
	amount = std::max(amount, 0);
	currentHp = std::max(currentHp - amount, 0);

	damageReactionTimer = DAMAGE_REACTION_TIME;
	isDamageReaction = true;

	pEnemySpawner->GetSoundManager().PlaySEAtPosition(RM().GetSound(ResourceKeys::Sound_EnemyDamage), position);


	if (currentHp == 0 && !isKilledReaction)
	{
		isKilledReaction = true;
		killedReactionTimer = KILLED_REACTION_TIME;

		explosion.Play({position.x, position.y + skin, position.z }, 450.0f, 0.2f, pEnemySpawner->GetSoundManager());

		pEnemySpawner->MoneyInc(dropCoin);

		if (pEnemySpawner) { pEnemySpawner->DecAliveEnemyCount(); }
	}
}

void Entity::TakeGroundDamage(int amount)
{
	if (groundDamageInvTimer > 0.0f) { return; }

	groundDamageInvTimer = groundDamageInvTime;
	
	TakeDamage(amount);
}

void Entity::DrawHpBar() const
{
	if (!isAlive) { return; }

	//0除算を防ぐ
	if (initHp <= 0.0f) { return; }

	//距離を取ったらバーを小さくしないと
	/*
	const float Distance = (pPlayer->GetPosition() - position).Length();
	constexpr float ScaleDownLimit = 2000.0f;
	float scaleDownRate = 0.0f;

	//Gap値が正なら縮小無し。マイナスなら小さくする。
	if (Distance > ScaleDownLimit){	scaleDownRate = 0.8f;}
	//int scaleReduceWidth = scaleDownRate * (hpBarWidth * 0.5f);
	//int scaleReduceHeight = scaleDownRate * (hpBarHeight * 0.5f);
	*/
	Vec3 hpBarPos = { position.x , position.y + 200.0f, position.z };

	VECTOR screenPosition = DxLib::ConvWorldPosToScreenPos(DxConv::ToVECTOR(hpBarPos));


	float p = static_cast<float>(currentHp) / static_cast<float>(initHp);

	constexpr int hpBarWidth = 256;
	int left = screenPosition.x - hpBarWidth / 2;
	int top = screenPosition.y  - hpBarHeight / 2;
	int right = left + hpBarWidth;
	int bottom = top + hpBarHeight;

	//色
	unsigned int OutLineColor = GetColor(0, 0, 0);
	unsigned int BackColor = GetColor(128, 32, 32);
	unsigned int HpColor = GetColor(0, 255, 0);

	DxLib::DrawBox(left, top, right					,bottom, OutLineColor, false, 10);
	DxLib::DrawBox(left, top, right					,bottom, BackColor, true);
	DxLib::DrawBox(left, top, left + hpBarWidth * p ,bottom, HpColor, true);
}

void Entity::StepGround(float deltaTime)
{
	const float toCoreDistance = (targetPosition - position).Length();

	//目的ポイントに到達
	if (toCoreDistance <= ROOTPOINT_DISTANCE_LIMIT)
	{
		const size_t ROOT_ARRAY_SIZE = pEnemyRoot->GetRootPointsLength();

		rootTargetIndex = std::min(rootTargetIndex + 1, ROOT_ARRAY_SIZE);

		isAlive = false;

		if (pEnemySpawner) 
		{ 
			pEnemySpawner->DecAliveEnemyCount(); 
			pEnemySpawner->CoreDamage(10);
			moveSpeed = 0.0f;
			return;
		}

		////目的ポイント != コア　だった時
		//if (pEnemyRoot)
		//{
		//	rootTargetPoint = pEnemyRoot->GetTargetPos(rootTargetIndex);

		//	//移動方向の更新
		//	moveDir = (rootTargetPoint - position).Normalized();
		//}
	}

	if (pPlayer)
	{
		if (!isDamageReaction && Collision::IsHitSphereSphere(pPlayer->GetPlayerSphere(), GetSphere()))
		{
			pPlayer->TakeDamage(coreDamage);
			TakeDamage(1);
		}
	}
	
	position += moveDir * moveSpeed * deltaTime;
}

bool Entity::IsClosePlayer()
{
	if (!pPlayer->IsAlive()) { return false; }

	float distance = (pPlayer->GetPosition() - position).LengthSq();
	int a = 0;
	return distance < ChaseStartDistance * ChaseStartDistance;
}

void Entity::SetTargetDirection()
{
	isChasePlayer = IsClosePlayer();

	if (isChasePlayer)
	{
		moveDir = (pPlayer->GetPosition() - position).Normalized();
		moveDir.y = 0;
	}
	else
	{
		moveDir = (targetPosition - position).Normalized();
	}
}