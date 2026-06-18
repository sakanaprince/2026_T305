#pragma once
#include "../DxPlus/DxPlus.h"
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
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	float pitch{ 0.0f };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	CameraController camera;
};

