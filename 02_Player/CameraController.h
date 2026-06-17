#pragma once
#include "DxPlus.h"
#include "../07_Math/Vector3.h"

class CameraController
{
public:
	void Reset();
	void Update(float deltaTime);

	const Vec3& GetEye() const { return eye; }
	void SetEye(const Vec3& e) { eye = e; }

	const Vec3& GetTarget() const { return target; }
	void SetTarget(const Vec3& t) { target = t; }

private:
	Vec3 eye{ 0.0f,0.0f,0.0f };
	Vec3 target{ 0.0f,0.0f,0.0f };
	Vec3 up{ 0.0f,1.0f,0.0f };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	float yaw{ 0.0f };
	float pitch{ 0.0f };
	float distance{ 800.0f };
	float dx{ 0.0f };
	float dy{ 0.0f };

	bool hasPrevMouse{ false };
};

