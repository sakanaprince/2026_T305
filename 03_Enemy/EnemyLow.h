#pragma once
#include "../01_Core/Entity.h"



class EnemyLow final : public Entity
{
public:
	void Init(EnemyRoot* enRoot) override;
	void Reset();
	void Update(float deltaTime) override;
	void Draw() const override;
	void DrawDebug()const override;

	void TakeDamage(int amount) override;



private:
	void BodyLine()const override;
	
};

