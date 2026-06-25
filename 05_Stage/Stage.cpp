#include "Stage.h"
#include "../04_Resource/ResourceManager.h"
#include "../04_Resource/ResourceKeys.h"
#include "../08_Debug/DebugUI.h"
#include "../07_Math/DxConv.h"

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
	scale = { 1.0f,1.0f,1.0f };
	MV1SetScale(modelHandle, DxConv::ToVECTOR(scale));
}

void Stage::Draw() const
{
	if (modelHandle < 0) { return; }

	MV1SetPosition(modelHandle, { 0.0f,0.0f,0.0f });
	MV1DrawModel(modelHandle);
}
