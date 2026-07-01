#include "EnemyQuick.h"
#include "../99_Utility/Const.h"

void EnemyQuick::Init(EnemyRoot* enRoot)
{
	radius = 80.0f;
	height = 40.0f;
	isAlive = false;
	pEnemyRoot = enRoot;

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"null Ptr enemyRoot_p");
		return;
	}
}

void EnemyQuick::Reset()
{
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	moveSpeed = 100.0f;
	rootTargetIndex = 0;
	currentHp = Const::ENEMY_LOW_MAXHP;

	damageReactionTimer = 0.0f;
	isDamageReaction = false;
	killedReactionTimer = 0.0f;
	isKilledReaction = false;

	if (pEnemyRoot)
	{
		position = pEnemyRoot->GetNextStartPos();
		rootTargetPoint = pEnemyRoot->GetCorePos();
		moveDir = (rootTargetPoint - position).Normalized();
	}

	isAlive = true;
}

void EnemyQuick::Update(float deltaTime)
{
}

void EnemyQuick::Draw() const
{
}

void EnemyQuick::DrawDebug() const
{
}

void EnemyQuick::TakeDamage(int amount)
{
}

void EnemyQuick::BodyLine() const
{
}
