#pragma once
#include "../DxPlus/DxPlus.h"
#include "CameraController.h"
#include "../07_Math/Vector3.h"
#include "../05_Stage/Stage.h"

class PlayerController
{
public:
	void Init();
	void Reset();
	void Update(float deltaTime);
	void Step(float deltaTime);
	void Draw() const;

private:
	Vec3 position{ 0.0f,50.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	float pitch{ 0.0f };
	float radius{ 30.0f };
	float halfHeight{ 50.0f };
	bool isGrounded{ true };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	CameraController camera;
	Stage stage;
};

