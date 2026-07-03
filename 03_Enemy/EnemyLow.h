#pragma once
#include "../01_Core/Entity.h"



class EnemyLow final : public Entity
{
public:
	void Init(EnemyRoot* enRoot, PlayerController* pc) override;
	void Reset();
	
	void DrawDebug()const override;


private:
	void BodyLine()const override;
};

