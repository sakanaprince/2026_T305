#include "EnemySpawner.h"
#include "../05_Stage/EnemyRoot.h"
#include "../03_Enemy/EnemyLow.h"

void EnemySpawner::Init(EnemyRoot* enR)
{
	for (auto& e : enemyCollection)
	{
		e.Init(enR);
		e.BindEnemySpawner(this);
	}
}


void EnemySpawner::Update(float deltaTime)
{
	spawnTimer += deltaTime;

	if (spawnTimer >= spawnDuration)
	{
		SpawnEnemy();
		spawnTimer = 0;
	}

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
	if (aliveEnemyCount > Const::MAX_ENEMY_COUNT){	return; }

	//非アクティブな敵が存在しないならreturn
	for (auto& e : enemyCollection)
	{
		if (e.IsAlive()) { continue; }

		aliveEnemyCount++;

		e.Reset();

		break;
	}

}


