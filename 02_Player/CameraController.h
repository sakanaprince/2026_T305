#pragma once
#include "DxLib.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"

class CameraController
{
public:
	CameraController() = default;

	void Reset(const Vec3& pos) { eye = pos; };

	void UpdateFromPlayer(const Vec3& pos, float yaw, float pitch)
	{
		eye = pos;

		float cosPitch = std::cos(pitch);
		float sinPitch = std::sin(pitch);
		float cosYaw = std::cos(yaw);
		float sinYaw = std::sin(yaw);

		Vec3 forwerd{ cosYaw * cosPitch,sinPitch,sinYaw * cosPitch };

		target = eye + forwerd;

		SetCameraPositionAndTargetAndUpVec(DxConv::ToVECTOR(eye), DxConv::ToVECTOR(target), DxConv::ToVECTOR(up));
	};

private:
	Vec3 eye{ 600.0f,600.0f,-600.0f };
	Vec3 target{ 0.0f,0.0f,0.0f };
	Vec3 up{ 0.0f,1.0f,0.0f };
};

