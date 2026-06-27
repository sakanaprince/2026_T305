#pragma once
#include <array>
#include "../03_Enemy/EnemyLow.h"

#include "../05_Stage/EnemyRoot.h"


class EnemySpawner
{
public:
	EnemySpawner() = default;
	void SpawnEnemy();
	void Init(EnemyRoot* enR);
	void Update(float deltaTime);
	void Draw() const;

	void DecAliveEnemyCount()
	{
		aliveEnemyCount--;
	}

private:
	static const int MAX_ENEMY_COUNT = 7;

	std::array<EnemyLow, MAX_ENEMY_COUNT> enemyCollection;
	int aliveEnemyCount = 0;
};

