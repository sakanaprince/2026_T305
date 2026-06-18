#pragma once
#include "../DxPlus/DxPlus.h"
#include "../07_Math/Vector3.h"

class CameraController
{
public:
	CameraController() = default;

	void UpdateFromPlayer(const Vec3& pos, float yaw, float pitch);

	const Vec3& GetEye() const { return eye; }
	void SetEye(const Vec3& e) { eye = e; }

	const Vec3& GetTarget() const { return target; }
	void SetTarget(const Vec3& t) { target = t; }

private:
	Vec3 eye{ 600.0f,600.0f,-600.0f };
	Vec3 target{ 0.0f,0.0f,0.0f };
	Vec3 up{ 0.0f,1.0f,0.0f };
};

