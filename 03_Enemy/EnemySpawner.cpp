#include "EnemySpawner.h"
#include "../05_Stage/EnemyRoot.h"

void EnemySpawner::Init(EnemyRoot* enR)
{
	for (auto& e : enemyCollection)
	{
		e.Init(enR);
	}
}


void EnemySpawner::Update(float deltaTime)
{
	for (auto& e : enemyCollection)
	{
		if (!e.IsAlive()) { continue; }

		e.Update(deltaTime);
	}
}

void EnemySpawner::Draw() const
{
	for (const auto& e : enemyCollection)
	{
		if (!e.IsAlive()) { continue; }

		e.Draw();
	}
}

void EnemySpawner::SpawnEnemy()
{
	if (aliveEnemyCount > MAX_ENEMY_COUNT){	return; }

	//非アクティブな敵が存在しないならreturn
	for (auto& e : enemyCollection)
	{
		if (e.IsAlive()) { continue; }

		aliveEnemyCount++;

		e.Reset();

		break;
	}

}


