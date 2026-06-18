#pragma once
#include "../03_Enemy/Enemy.h"

class EnemyLow final : public Enemy
{
public:
	void BodyLine() const override;

	void Init()override;
	void Update() override;
	void Draw() const override;

};

