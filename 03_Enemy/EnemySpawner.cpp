#include "EnemySpawner.h"
#include "../01_Core/GameContext.h"

#include "../05_Stage/EnemyRoot.h"
#include "../03_Enemy/EnemyLow.h"
#include "../03_Enemy/EnemyQuick.h"
#include "../03_Enemy/EnemyTank.h"
#include "../03_Enemy/EnemyFly.h"

#include "../08_Debug/DebugUI.h"

#include <iterator>

void EnemySpawner::Init(EnemyRoot* enR, PlayerController* pc, GameContext* gC)
{
	pGameContext = gC;

	enemyCollection.reserve(Const::MAX_ENEMY_COUNT);
	spawnedCount = 0;
	aliveEnemyCount = 0;

	initLimitTimer = pGameContext->GetLimit_Timer();
	//プール初期化
	for (int i = 0; i < Const::MAX_SAME_ENEMY_POOL_COUNT; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyLow>()); 
		
		enemyCollection[i]->Init(enR, pc);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 2; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyQuick>());

		enemyCollection[i]->Init(enR, pc);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT * 2; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 3; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyTank>());

		enemyCollection[i]->Init(enR, pc);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT * 3; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 4; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyFly>());

		enemyCollection[i]->Init(enR, pc);
		enemyCollection[i]->BindEnemySpawner(this);
	}
}


void EnemySpawner::Update(float deltaTime)
{
	spawnTimer += deltaTime;

	float firstTimer = spawnedCount * 0.2f;

	if (firstTimer > 4.0f)
	{
		firstTimer = 4.0f;
	}


	if (spawnTimer >= spawnDuration - firstTimer)
	{
		//敵を全員出現させるサイクル
		int spawnCycle = spawnedCount % static_cast<int>( ENEMY_NAME::AllEnemyNameCount);
		SpawnEnemy(static_cast<ENEMY_NAME>(spawnCycle));
		//SpawnEnemy(ENEMY_NAME::Quick);

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
	
#ifdef _DEBUG
	for (const auto& e : enemyCollection)
	{
		if (!e->IsAlive()) { continue; }

		e->DrawDebug();
	}
#endif

}


const void EnemySpawner::CoreDamage(int damage) const
{
	if (!pGameContext)
	{
		DxPlus::Utils::FatalError(L"Pointer GameContextがないバインド忘れてる by EnemySpaner");
	}

	pGameContext->GetCore().TakeDamage(damage);
}

const void EnemySpawner::MoneyInc(int money) const
{
	//if (!pGameContext)
	//{
	//	DxPlus::Utils::FatalError(L"Pointer GameContextがないバインド忘れてる EnemySpanerがいってる");
	//}

	//pGameContext->GetCore().
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
	else if (enName == ENEMY_NAME::Quick){startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT;}
	else if (enName == ENEMY_NAME::Tank) {startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT * 2;}
	else if (enName == ENEMY_NAME::Fly) {startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT * 3;}

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


