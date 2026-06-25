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
	position = { 0.0f,0.0f,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	radius = { 5.0f };
	life = { 3.0f };
	isActive = { false };
}

void Bullet::Update(float deltaTime)
{
	if (!isActive)return;

	position += velocity * deltaTime;
	life -= 1 * deltaTime;

	if (life <= 0)
		isActive = false;
}

void Bullet::Draw() const
{
	if (!isActive)return;

	//’eŠÛ(‹…)
	DrawSphere3D(DxConv::ToVECTOR(position), radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	//’eŠÛ‚ÌŽc‘œ(ü)
	Vec3 tail = position - velocity.Normalized() * 10;
	DrawLine3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(tail), GetColor(255, 200, 50));
}

void Bullet::Fire(const Vec3& pos, const Vec3& dir)
{
	position = pos;
	velocity = dir.Normalized() * Const::BULLET_SPEED;
	life = 3.0f;
	isActive = true;
}
