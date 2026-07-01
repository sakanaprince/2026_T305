#pragma once
#include <array>
#include "../01_Core/Entity.h"

#include "../05_Stage/EnemyRoot.h"

#include "../99_Utility/Const.h"

#include <vector>
class EnemySpawner
{
public:
	EnemySpawner() = default;
	void Init(EnemyRoot* enR);
	void Update(float deltaTime);
	void Draw() const;

	void DecAliveEnemyCount()
	{
		aliveEnemyCount--;
	}


	/// <summary>
	/// 引数番目の敵の”参照”返す、indexの値確認は呼び出しもとで注意してね
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	auto& GetEnemy(size_t index) { return enemyCollection[index]; }

private:
	void SpawnEnemy();

	//std::array<Entity, Const::MAX_ENEMY_COUNT> enemyCollection{};
	std::vector<std::unique_ptr<Entity>> enemyCollection;

	int aliveEnemyCount = 0;

	float spawnTimer{ 0.0f };
	const float spawnDuration{ 1.0f };
};

