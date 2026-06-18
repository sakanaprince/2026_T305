#pragma once
#include "DxLib.h"
#include "DxPlus.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"

class CameraController
{
public:
	CameraController() = default;

	void Reset(const Vec3& pos)
	{
		eye = pos;
		target = { 0.0f,0.0f,0.0f };
		up = { 0.0f,1.0f,0.0f };
	};

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

	void Draw()const
	{
		int cx = DxPlus::CLIENT_WIDTH / 2;
		int cy = DxPlus::CLIENT_HEIGHT / 2;

		int size = 10;
		int thick = 5;
		int color = GetColor(128, 128, 128);

		DrawLine(cx - size, cy, cx + size, cy, color, thick);
		DrawLine(cx, cy - size, cx, cy + size, color, thick);
	}

private:
	Vec3 eye{ 0.0f,0.0f,0.0f };
	Vec3 target{ 0.0f,0.0f,0.0f };
	Vec3 up{ 0.0f,1.0f,0.0f };
};

