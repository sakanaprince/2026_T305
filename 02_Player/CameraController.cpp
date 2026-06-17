#include "CameraController.h"
#include "DxLib.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"

void CameraController::Reset()
{
	hasPrevMouse = { false };
	target = { 0.0f,0.0f,0.0f };
	yaw = 0.0f;
	pitch = 0.0f;
	distance = 0.0f;

	float cosPitch = std::cos(pitch);
	float sinPitch = std::sin(pitch);
	float cosYaw = std::cos(yaw);
	float sinYaw = std::sin(yaw);

	Vec3 offset{ cosYaw * cosPitch,sinPitch,sinYaw * sinPitch };
	eye = target + offset * distance;
	up = { 0.0f,1.0f,0.0f };

	SetCameraPositionAndTargetAndUpVec(DxConv::ToVECTOR(eye), DxConv::ToVECTOR(target), DxConv::ToVECTOR(up));
}

void CameraController::Update(float deltaTime)
{
}
