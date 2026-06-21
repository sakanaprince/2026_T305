#pragma once
#include "../01_Core/Entity.h"

class EnemyLow final : public Entity
{
public:
 
	void Init() override;

	void Update(float deltaTime) override;
	void Draw() const override;
	void DrawDebug()const override;

private:
	void BodyLine() const ;
	float animTimer{ 0.0f };
};

