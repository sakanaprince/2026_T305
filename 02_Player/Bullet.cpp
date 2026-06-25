#include "Bullet.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"

void Bullet::Init()
{
}

void Bullet::Reset()
{
	position = { 0.0f,0.0f,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	radius = { 1.0f };
	isActive = { false };
}

void Bullet::Update()
{
}

void Bullet::Draw() const
{
	if (!isActive)return;

	//íeä€(ãÖ)
	DrawSphere3D(DxConv::ToVECTOR(position), radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	//íeä€ÇÃécëú(ê¸)
	Vec3 tail = position - velocity.Normalized() * 10;
	DrawLine3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(tail), GetColor(255, 200, 50));
}
