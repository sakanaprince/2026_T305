#pragma once
#include "Scene.h"

class ResultScene final : public Scene
{
	
public:
	ResultScene() = default;

	// Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
};

