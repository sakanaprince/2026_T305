#pragma once
#include "../01_Core/Entity.h"

class EnemyFly final : public Entity
{
public:
	void Reset();
	void Update(float deltaTime)override;
	void DrawDebug()const override;
	void StepGround(float deltaTime) override;
	
	
	void ExplosionUpdate(float deltaTime) override;
	void ExplosionDraw() const override;

private:
	void BodyLine()const override;
	float gravity{ 0.0f };
	
};
