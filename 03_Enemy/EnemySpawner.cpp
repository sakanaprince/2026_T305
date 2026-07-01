#include "EnemySpawner.h"
#include "../05_Stage/EnemyRoot.h"
#include "../03_Enemy/EnemyLow.h"
#include "../03_Enemy/EnemyQuick.h"
#include <iterator>

void EnemySpawner::Init(EnemyRoot* enR)
{
	enemyCollection.reserve(Const::MAX_ENEMY_COUNT);
	spawnedCount = 0;
	aliveEnemyCount = 0;

	//プール初期化
	for (int i = 0; i < Const::MAX_SAME_ENEMY_POOL_COUNT; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyLow>()); 
		
		enemyCollection[i]->Init(enR);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 2; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyQuick>());

		enemyCollection[i]->Init(enR);
		enemyCollection[i]->BindEnemySpawner(this);
	}

	//とりあえずvectorの中身を要素で埋めよう
	//for (int i = 0; i < 10; i++)
	//{
	//	enemyCollection.push_back(std::make_unique<EnemyQuick>());

	//	enemyCollection[i]->Init(enR);
	//	enemyCollection[i]->BindEnemySpawner(this);
	//}

	//for (auto& e : enemyCollection)
	//{
	// 
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
		if (spawnedCount % 3 == 0){SpawnEnemy(ENEMY_NAME::Quick);}
		else{SpawnEnemy(ENEMY_NAME::Low);}
		
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


void EnemySpawner::SpawnEnemy(ENEMY_NAME enName)
{
	//出現限界の数を超えてるならreturn
	if (aliveEnemyCount > Const::MAX_ENEMY_COUNT){	return; }

	//呼んではいけないAllCountが引数ならreturn
	if (enName == ENEMY_NAME::AllEnemyNameCount) { return; }

	//嗚呼今は基底クラスのEntityを召喚してしまっているのか（自力で解決済み makeUnique使えばよかった）

	//ENUMをあてにしてどうやって生成するクラスを変える？
	//そのために必要なのは全敵を管理しているenemyCollection配列に工夫が必要かも。
	//例えば 0から10番目まではLowで11番目から20番目まではQuickみたいな。(自力で解決済み この考察が当たっていた)
	

	size_t startIndex = 0;

	if (enName == ENEMY_NAME::Low){startIndex = 0;}
	if (enName == ENEMY_NAME::Quick){startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT;}

	//待機状態の敵を探してResetする
	for (size_t i = startIndex; i < startIndex + Const::MAX_SAME_ENEMY_POOL_COUNT; i++)
	{
		if (enemyCollection[i]->IsAlive()) { continue; }

		spawnedCount++;
		aliveEnemyCount++;

		enemyCollection[i]->Reset();

		break;
	}
}


