#pragma once
#include "../01_Core/Entity.h"

class EnemySpawner;

class EnemyLow final : public Entity
{
public:
	void Init(EnemyRoot* enRoot) override;
	void Reset();
	void Update(float deltaTime) override;
	void Draw() const override;
	void DrawDebug()const override;

	/// <summary>
	/// GameContext‚Å•R‚Ã‚¯‚Ä‚à‚ç‚¤
	/// </summary>
	void BindEnemySpawner(EnemySpawner* enSpawner) { pEnemySpawner = enSpawner; }

private:
	void BodyLine() const ;
	float animTimer{ 0.0f };
	
	const float  DISTANCE_LIMIT = 10.0f;
	EnemySpawner* pEnemySpawner{ nullptr };

};

