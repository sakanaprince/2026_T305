#pragma once
#include "../01_Core/Entity.h"
class EnemyTank final : public Entity
{
public:
	// Entity ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Init(EnemyRoot* enRoot, PlayerController* pc) override;
	void Reset();
	void Update(float deltaTime) override;
	void Draw() const override;
	void DrawDebug()const override;
private:
	void BodyLine()const override;
};

