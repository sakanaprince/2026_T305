#pragma once
#include "Scene.h"

class GameScene : public Scene
{
	// Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½...‚Â‚Ü‚èprotected
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;


public:
	GameScene() = default;

private:
};

