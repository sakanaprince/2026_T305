#include "CameraController.h"
#include "DxLib.h"
#include "DxPlus.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"
#include "../99_Utility/Const.h"

void CameraController::Reset()
{
	hasPrevMouse = { false };
	target = { 0.0f,0.0f,0.0f };
	yaw = 0.0f;
	pitch = 0.0f;
	distance = 800.0f;

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
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	if (!hasPrevMouse) {
		prevMouse = currentMouse;
		hasPrevMouse = true;
		return;
	}

	dx = float(currentMouse.x - prevMouse.x);
	dy = float(currentMouse.y - prevMouse.y);

	yaw += dx + Const::ROTATE_RAD_PAR_PIXEL;
	pitch += dy + Const::ROTATE_RAD_PAR_PIXEL;
	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);

	prevMouse = currentMouse;

	float cosPitch = std::cos(pitch);
	float sinPitch = std::sin(pitch);
	float cosYaw = std::cos(yaw);
	float sinYaw = std::sin(yaw);

	Vec3 offset{ cosYaw * cosPitch,sinPitch,sinYaw * sinPitch };
	eye = target + offset * distance;
	up = { 0.0f,1.0f,0.0f };

	SetCameraPositionAndTargetAndUpVec(DxConv::ToVECTOR(eye), DxConv::ToVECTOR(target), DxConv::ToVECTOR(up));
}
