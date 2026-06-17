#pragma once
#include "CameraController.h"
#include "../07_Math/Vector3.h"

class PlayerController
{
public:
	void Init();
	void Reset();
	void Update(float deltaTime);
	void Step(float deltaTime);
	void Draw();

private:
	Vec3 position{ 0.0f,0.0f,0.0f };

	CameraController camera;
};

