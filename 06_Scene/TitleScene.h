#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:

	TitleScene() = default;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;

private:
};



