#pragma once
#include <unordered_map>
#include <memory>
#include "../json.hpp"
#include <vector>

enum class EnemyKey
{
	Low,
	Quick,
	Fly,
	Tank,
};

NLOHMANN_JSON_SERIALIZE_ENUM(EnemyKey,
	{
		{EnemyKey::Low,		"Low"},
		{EnemyKey::Quick,	"Quick"},
		{EnemyKey::Fly,		"Fly"},
		{EnemyKey::Tank,	"Tank"}
	}
)

struct EnemyWave
{
	EnemyKey key;
	int spawnCount;
	float spawnDelay;
};



struct EnemyStatus
{
	EnemyKey key;
	int maxHp;
	int moveSpeed;
	int coreDamage;
	int dropCoin;
};

class EnemyDataMaster
{
public:
	void LoadJson();
	std::shared_ptr<EnemyStatus> GetEnemyStatus(EnemyKey key);

	size_t GetEnemyWaveSize() { return enemyWaves.size(); }
	std::shared_ptr<EnemyWave> GetEnemyWave(size_t idx);

private:
	std::unordered_map<EnemyKey, std::shared_ptr<EnemyStatus>> enemyAllData;
	std::vector<std::shared_ptr<EnemyWave>> enemyWaves;
	
};

