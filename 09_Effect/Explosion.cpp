#include "Explosion.h"
#include "../07_Math/DxConv.h"
void Explosion::Update(float deltaTime)
{
	if (!isActive) { return; }
	timer += deltaTime;

	if (timer >= endExplosionTimer)
	{
		isActive = false;
	}
}

void Explosion::Draw() const
{
	if (!isActive) { return; }

	float p = timer / endExplosionTimer;
	int blendPram = 220;
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, blendPram);
	DrawSphere3D(DxConv::ToVECTOR(position), explosionRadius * p, 16, GetColor(255, 190, 0), GetColor(255, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
