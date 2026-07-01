#include "EnemySpawner.h"
#include "../05_Stage/EnemyRoot.h"
#include "../03_Enemy/EnemyLow.h"
#include <iterator>

void EnemySpawner::Init(EnemyRoot* enR)
{
	enemyCollection.reserve(Const::MAX_ENEMY_COUNT);

	for (int i = 0; i < Const::MAX_ENEMY_COUNT; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyLow>());
		enemyCollection[i]->Init(enR);
		enemyCollection[i]->BindEnemySpawner(this);
	}

	//for (auto& e : enemyCollection)
	//{
	//	//初期化するEnitityリストの中に「EnemyLowクラス」「EnemyQuickクラス」...と初期化したい
	//	

	//	e->Init(enR);
	//	e->BindEnemySpawner(this);
	//}
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
		if (!e->IsAlive()) { continue; }

		e->Update(deltaTime);
	}
}

void EnemySpawner::Draw() const
{
	for (const auto& e : enemyCollection)
	{
		if (!e->IsAlive()) { continue; }

		e->Draw();
	}
}


void EnemySpawner::SpawnEnemy()
{
	if (aliveEnemyCount > Const::MAX_ENEMY_COUNT){	return; }

	//非アクティブな敵が存在しないならreturn

	//嗚呼今は基底クラスのEnittyを召喚してしまっているのか
	for (auto& e : enemyCollection)
	{
		if (e->IsAlive()) { continue; }

		aliveEnemyCount++;

		e->Reset();

		break;
	}

}


