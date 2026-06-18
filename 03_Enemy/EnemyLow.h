#pragma once
#include "../03_Enemy/Enemy.h"

class EnemyLow final : public Enemy
{
public:
	void BodyLine() const override;
 

	void Update() override;
	void Draw() const override;
	void DrawDebug()const override;


	// Enemy ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Init() override
	{
		radius = 200.0f;
		height = 250.0f;
	};

};

