#include "Bullet.h"
#include "DxLib.h"
#include "DxPlus.h"
#include "../07_Math/DxConv.h"
#include "../99_Utility/Const.h"

void Bullet::Init()
{
}

void Bullet::Reset()
{
	bullet.radius = { 5.0f };
	velocity = { 0.0f,0.0f,0.0f };
	maxLife = { 2.0f };
	life = { maxLife };
	isActive = { false };
}

void Bullet::Update(float deltaTime)
{
	if (!isActive)return;

	bullet.centerPos += velocity * deltaTime;
	life -= deltaTime;

	if (life <= 0)
		DeActivate();
}

void Bullet::Draw() const
{
	if (!isActive)return;

	//’eŠÛ(‹…)
	DrawSphere3D(DxConv::ToVECTOR(bullet.centerPos), bullet.radius, 8,
		GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	//’eŠÛ‚ÌŽc‘œ(ü)
	Vec3 tail = bullet.centerPos - velocity.Normalized() * 20;
	DrawLine3D(DxConv::ToVECTOR(bullet.centerPos), DxConv::ToVECTOR(tail), GetColor(255, 0, 0));
}

void Bullet::Fire(const Vec3& pos, const Vec3& dir)
{
	bullet.centerPos = pos;
	velocity = dir.Normalized() * Const::BULLET_SPEED;
	life = maxLife;
	isActive = true;
}
