#pragma once
#include <array>
#include "../01_Core/Entity.h"

#include "../05_Stage/EnemyRoot.h"

#include "../99_Utility/Const.h"

#include <vector>

class GameContext;
class EnemySpawner
{
public:
	EnemySpawner() = default;
	void Init(EnemyRoot* enRoot, PlayerController* pc, GameContext* gC);
	void Update(float deltaTime);
	void Draw() const;



	const void CoreDamage(int damage) const;

	void DecAliveEnemyCount()
	{
		aliveEnemyCount--;
	}

	enum class ENEMY_NAME
	{
		Low = 0,
		Quick,
		Tank,
		Fly,

		//AllEnemyNameCountは全部で何種類の敵がいるかを返す
		AllEnemyNameCount
	};


	/// <summary>
	/// 引数番目の敵の”参照”返す、indexの値確認は呼び出しもとで注意してね
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	auto& GetEnemy(size_t index) { return enemyCollection[index]; }

	/// <summary>
	/// コレクションVectorの要素数を取得できる
	/// </summary>
	/// <returns></returns>
	size_t GetEnemyCollectionSize() { return enemyCollection.size(); }

private:
	void SpawnEnemy(ENEMY_NAME enName);

	GameContext* pGameContext{ nullptr };

	std::vector<std::unique_ptr<Entity>> enemyCollection;

	int aliveEnemyCount = 0;

	float spawnTimer{ 0.0f };
	const float spawnDuration{ 5.0f };

	int spawnedCount{ 0 };

	float initLimitTimer{ 0 };
};

