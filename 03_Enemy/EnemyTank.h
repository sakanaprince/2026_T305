#pragma once
#include "../01_Core/Entity.h"
class EnemyTank final : public Entity
{
public:
	void Reset();
	void Draw() const override;
	void DrawDebug()const override;
private:
	void BodyLine()const override;
};

