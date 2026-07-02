#include "Entity.h"
#include "../03_Enemy/EnemySpawner.h"

void Entity::StepGround(float deltaTime)
{
	const float rootTargetPointDistance = (rootTargetPoint - position).Length();

	//目的ポイントに到達
	if (rootTargetPointDistance <= ROOTPOINT_DISTANCE_LIMIT)
	{
		const size_t ROOT_ARRAY_SIZE = pEnemyRoot->GetRootPointsLength();

		rootTargetIndex = std::min(rootTargetIndex + 1, ROOT_ARRAY_SIZE);

		//目的ポイント == コア　だった時
		if (rootTargetIndex >= ROOT_ARRAY_SIZE)
		{
			isAlive = false;

			MessageBox(NULL, L"とうたつ", L"", FALSE);
			if (pEnemySpawner) { pEnemySpawner->DecAliveEnemyCount(); }

			return;
		}

		//目的ポイント != コア　だった時
		if (pEnemyRoot)
		{
			rootTargetPoint = pEnemyRoot->GetTargetPos(rootTargetIndex);

			//移動方向の更新
			moveDir = (rootTargetPoint - position).Normalized();
		}
	}

	if (pPlayer)
	{
		int a = 0;

		if (!isDamageReaction && Collision::IsHitSphereSphere(pPlayer->GetPlayerSphere(), GetSphere()))
		{
			pPlayer->TakeDamage(2);
			TakeDamage(1);
		}
	}
	
	position += moveDir * moveSpeed * deltaTime;
}

/*

constexpr int ENEMY_LOW_MAXHP{ 3 };
	constexpr int MAX_ENEMY_COUNT{ 20 };
	constexpr int MAX_SAME_ENEMY_POOL_COUNT{ 10 };
*/