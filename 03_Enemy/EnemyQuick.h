#pragma once
#include "../01_Core/Entity.h"

class EnemyQuick : public Entity
{
public:
	void Reset();
	void DrawDebug()const override;

private:
	void BodyLine()const override;

};

