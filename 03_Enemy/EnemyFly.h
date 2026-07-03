#pragma once
#include "../01_Core/Entity.h"

class EnemyFly final : public Entity
{
public:
	void Init(EnemyRoot* enRoot, PlayerController* pc) override;
	void Reset();
	void Draw() const override;
	void DrawDebug()const override;


private:
	void BodyLine()const override;
};
