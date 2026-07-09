#pragma once
#include <array>
#include "../01_Core/Entity.h"

#include "../05_Stage/EnemyRoot.h"

#include "../99_Utility/Const.h"

#include <vector>

class GameContext;
class EnemyDataMaster;
class SoundManager;

class EnemySpawner
{
public:
	EnemySpawner() = default;
	void Init(EnemyRoot* enRoot, PlayerController* pc, GameContext* gC, EnemyDataMaster* eD);
	void Reset();
	void Update(float deltaTime);
	void Draw() const;

	void DrawMiniMap() const;
	const void CoreDamage(int damage) const;
	const void MoneyInc(int money) const;
	SoundManager& GetSoundManager();
	/// <summary>
	/// ショップ閉じた後で反映されるために時間差を作っておいた
	/// </summary>
	/// <returns>すでに全敵ダメージ関数が呼ばれている最中ならFALSE</returns>
	bool ReadyAllEnemyTakeDamage(int dmg, float delayTime);

	void DecAliveEnemyCount()
	{
		aliveEnemyCount--;
	}

	//enum class ENEMY_NAME
	//{
	//	Low = 0,
	//	Quick,
	//	Tank,
	//	Fly,

	//	//AllEnemyNameCountは全部で何種類の敵がいるかを返す
	//	AllEnemyNameCount
	//};


	/// <summary>
	/// 引数番目の敵の”参照”返す、indexの値確認は呼び出しもとで注意してね
	/// </summary>
	auto& GetEnemy(size_t index) { return enemyCollection[index]; }

	/// <summary>
	/// コレクションVectorの要素数を取得できる
	/// </summary>
	size_t GetEnemyCollectionSize() { return enemyCollection.size(); }

	void PlaySoundPos(int handle, Vec3 pos);
	void EndGame();
	

private:
	void SpawnEnemy(EnemyKey enName);

	GameContext* pGameContext{ nullptr };

	std::vector<std::unique_ptr<Entity>> enemyCollection;

	int aliveEnemyCount = 0;

	float spawnTimer{ 0.0f };
	const float spawnDuration{ 5.0f };
	int spawnedCount{ 0 };


	//ウェーブ関連
	EnemyDataMaster* pEnemyDataMaster{ nullptr };

	size_t maxWave{ 0 };
	size_t currentWave{ 0 };
	int waveSpawned{ 0 };
	float nextSpawnTime{ 0.0f };

	//ゲーム開始時のクリアまでの残り時間を覚えておく
	float gameStartLeftTime{ 0 };


	//時間差全体攻撃
	float allEnemyTakeDamageDelayTimer{ 0.0f };
	float allEnemyTakeDamageDelayTime{ 0.0f };
	bool nowAllEnemyTakeDamage{ false };
	int allEnemyTakeDamageAmount{ 0 };
};

