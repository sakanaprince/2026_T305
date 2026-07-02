#pragma once
#include "../01_Core/Entity.h"

class EnemyFly final : public Entity
{
public:
	void Init(EnemyRoot* enRoot, PlayerController* pc) override;
	void Reset();
	void Update(float deltaTime) override;
	void Draw() const override;
	void DrawDebug()const override;

	void TakeDamage(int amount) override;


private:
	void BodyLine()const override;
	int initHp{ 10 };
};
