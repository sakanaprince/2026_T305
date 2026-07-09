#pragma once
#include <unordered_map>
#include <memory>
#include "../json.hpp"

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

private:
	std::unordered_map<EnemyKey, std::shared_ptr<EnemyStatus>> enemyAllData;

	
};

