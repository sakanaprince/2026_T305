#include "Arrow.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"
#include "../10_Physics/Raycast.h"
#include "../08_Debug/DebugUI.h"

void Arrow::Init()
{
	modelHandle = RM().GetModel(ResourceKeys::Model_Arrow);
}

void Arrow::Reset()
{
	position = { 0.0f ,0.0f ,0.0f };
	scale = { 2.0f,2.0f,2.0f };
	velocity = { 0.0f, 0.0f, 0.0f };
	isActive = false;
	MV1SetScale(modelHandle, DxConv::ToVECTOR(scale));
}


void Arrow::Update(float deltaTime)
{
	position += velocity * speed * deltaTime;

	lifeTimer -= deltaTime;


	//一旦レイキャストは使わない
	//Physics::RayHit ray;
	//Vec3 start = position;
	//start.y += 3.0f;
	//Vec3 end = position + velocity * 6.0f;
	//end.y += 3.0f;

	if (lifeTimer <= 0/* || Physics::Raycast(stage.GetModelHandle(), start, end, ray)*/)
	{
		Debug().Log("Kill");
		isActive = false;
	}
}

void Arrow::Draw() const
{
	MV1SetPosition(modelHandle, DxConv::ToVECTOR(position));
	MV1SetRotationXYZ(modelHandle, DxConv::ToVECTOR({ 0.0f, yaw, 0.0f }));
	MV1DrawModel(modelHandle);
}

void Arrow::LaunchArrow(Vec3 forward, float deltaTime, Turret& turret)
{
	velocity = forward * speed * deltaTime;
	position = turret.GetPosition();
	position.y += 36.0f;
	lifeTimer = lifeTime;
	isActive = true;
	MV1SetPosition(modelHandle, DxConv::ToVECTOR(position));
	MV1SetRotationXYZ(modelHandle, DxConv::ToVECTOR({ 0.0f, turret.GetYaw(), 0.0f}));
	yaw = turret.GetYaw();
}
