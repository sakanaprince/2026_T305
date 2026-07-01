#pragma once
#include "../01_Core/Entity.h"

class EnemyQuick : public Entity
{
public:
	// Entity ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Init(EnemyRoot* enRoot) override;
	void Reset();
	void Update(float deltaTime) override;
	void Draw() const override;
	void DrawDebug()const override;

	void TakeDamage(int amount) override;
private:
	void BodyLine()const override;
};

