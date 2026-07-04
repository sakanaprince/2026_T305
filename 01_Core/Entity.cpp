#include "Entity.h"
#include "../03_Enemy/EnemySpawner.h"


void Entity::Update(float deltaTime)
{
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
	if (!isAlive) { return; }

	//プレイヤーの視野に入っていないならretrun(軽量化)
	bool isPlayerView = false;
	Vec3 playerPos = position - pPlayer->GetPosition();
	Vec3 playerForward = pPlayer->GetForward();

	float dot_startToTargetVecAndSightVec = Vec3::Dot(playerPos, playerForward);

	float scara_startToTarget = sqrtf(playerPos.x * playerPos.x + playerPos.z * playerPos.z);
	float scara_sight = sqrtf(playerForward.x * playerForward.x + playerForward.z * playerForward.z);

	float digCosSeata = dot_startToTargetVecAndSightVec / (scara_startToTarget * scara_sight);

	const float playerSightAngle = cos(DxPlus::Deg2Rad * 50);

	DxPlus::Debug::SetFormatString(L"COS SETA %.2f, ANGLE %.2f", digCosSeata, playerSightAngle);

	if (digCosSeata > playerSightAngle) { isPlayerView = true; }

	if (!isPlayerView) { return; }

	BodyLine();
	DrawHpBar();
}

void Entity::TakeDamage(int amount)
{
	if (isKilledReaction) { return; }

	amount = std::max(amount, 0);
	currentHp = std::max(currentHp - amount, 0);

	damageReactionTimer = DAMAGE_REACTION_TIME;
	isDamageReaction = true;

	if (currentHp == 0 && !isKilledReaction)
	{
		isKilledReaction = true;
		killedReactionTimer = KILLED_REACTION_TIME;

		explosion.Play({position.x, position.y + skin, position.z }, 250.0f, 0.2f);
		
		//お金を増やす処理が必要
		pEnemySpawner->MoneyInc(10);

		if (pEnemySpawner) { pEnemySpawner->DecAliveEnemyCount(); }
	}
}

void Entity::DrawHpBar() const
{
	if (!isAlive) { return; }

	//距離を取ったらバーを小さくしないと
	Vec3 hpBarPos = { position.x - 100.0f, position.y + 200.0f, position.z };

	VECTOR finalPos = DxLib::ConvWorldPosToScreenPos(DxConv::ToVECTOR(hpBarPos));

	float p = static_cast<float>(currentHp) / static_cast<float>(initHp);

	DxPlus::Primitive2D::DrawRect({finalPos.x- 128, finalPos.y +  10.0f},{256,hpBarHeight},GetColor(255,0,0),true );
	DxPlus::Primitive2D::DrawRect({finalPos.x- 128, finalPos.y +  10.0f},{256 * p,hpBarHeight},GetColor(0,255,0),true );
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
			pPlayer->TakeDamage(2);
			TakeDamage(1);
		}
	}
	
	position += moveDir * moveSpeed * deltaTime;
}

bool Entity::IsClosePlayer()
{
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

/*

constexpr int ENEMY_LOW_MAXHP{ 3 };
	constexpr int MAX_ENEMY_COUNT{ 20 };
	constexpr int MAX_SAME_ENEMY_POOL_COUNT{ 10 };
*/