#include "Stage.h"
#include "../04_Resource/ResourceManager.h"
#include "../04_Resource/ResourceKeys.h"
#include "../08_Debug/DebugUI.h"
#include "../07_Math/DxConv.h"
#include "../10_Physics/Raycast.h"

void Stage::Init()
{
	modelHandle = RM().GetModel(ResourceKeys::Model_Stage);

	if (modelHandle < 0) 
	{
		MV1SetupCollInfo(modelHandle, -1, 8, 8, 8);
	}
}

void Stage::Reset()
{
	scale = { 2.0f,2.0f,2.0f };
	MV1SetScale(modelHandle, DxConv::ToVECTOR(scale));
}

void Stage::Draw() const
{
	if (modelHandle < 0) { return; }

	MV1SetPosition(modelHandle, { 0.0f,0.0f,0.0f });
	MV1DrawModel(modelHandle);
}

float Stage::GetGroundHeight(const Vec3& pos)
{
	Physics::RayHit hit;
	float maxDist = 1000.0f;

	Vec3 start = pos + Vec3(0, 20.0f, 0);
	Vec3 end = pos - Vec3(0, maxDist, 0);

	if (Physics::Raycast(modelHandle, start, end, hit)) {
		return hit.point.y;
	}

	return 0.0f;
}
