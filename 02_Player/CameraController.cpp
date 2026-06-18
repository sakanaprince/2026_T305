#include "CameraController.h"
#include "DxLib.h"
#include "DxPlus.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"
#include "../99_Utility/Const.h"

void CameraController::UpdateFromPlayer(const Vec3& pos, float yaw, float pitch)
{
	eye = pos;

	float cosPitch = std::cos(pitch);
	float sinPitch = std::sin(pitch);
	float cosYaw = std::cos(yaw);
	float sinYaw = std::sin(yaw);

	Vec3 forwerd{ cosYaw * cosPitch,sinPitch,sinYaw * cosPitch };

	target = eye + forwerd;

	SetCameraPositionAndTargetAndUpVec(DxConv::ToVECTOR(eye), DxConv::ToVECTOR(target), DxConv::ToVECTOR(up));
}
