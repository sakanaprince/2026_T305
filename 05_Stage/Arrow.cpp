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

	//scaleの平均を*5した値をradiusにする
	sphereArrow.radius = ((scale.x + scale.y + scale.z) / 3) * 5;

	MV1SetScale(modelHandle, DxConv::ToVECTOR(scale));
}


void Arrow::Update(float deltaTime)
{
	position += velocity * speed * deltaTime;

	sphereArrow.centerPos = position + velocity * (scale.z * 20);
	sphereArrow.centerPos.y = position.y + (scale.y * 2.5f);

	lifeTimer -= deltaTime;

	//時間経過で削除
	if (lifeTimer <= 0)
	{
		Kill();
	}
}

void Arrow::Draw() const
{
	MV1SetPosition(modelHandle, DxConv::ToVECTOR(position));
	MV1SetRotationXYZ(modelHandle, DxConv::ToVECTOR({ 0.0f, yaw, 0.0f }));
	MV1DrawModel(modelHandle);

	//デバッグ用の当たり判定表示
#ifndef NDEBUG
	if (isActive)
	{
		DrawSphere3D(DxConv::ToVECTOR(sphereArrow.centerPos), sphereArrow.radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
	}
#endif // DEBUG
}

void Arrow::LaunchArrow(Vec3 forward, float deltaTime, Turret& turret)
{
	velocity = forward;
	position = turret.GetPosition();
	//矢の発射位置調整
	position.y += turret.GetScale().y * 40.0f;

	//当たり判定の位置設定
	sphereArrow.centerPos = position + velocity * (scale.z * 20);
	sphereArrow.centerPos.y = position.y + (scale.y * 2.5f);

	lifeTimer = lifeTime;
	isActive = true;
	MV1SetPosition(modelHandle, DxConv::ToVECTOR(position));
	MV1SetRotationXYZ(modelHandle, DxConv::ToVECTOR({ 0.0f, turret.GetYaw(), 0.0f}));
	yaw = turret.GetYaw();
}
