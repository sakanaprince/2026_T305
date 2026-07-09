#pragma once
#include "../DxPlus/DxPlus.h"
#include "../07_Math/Vector3.h"
#include "../12_Sound/SoundManager.h"
#include "../04_Resource/ResourceManager.h"
class Explosion
{
public:
	Explosion() = default;

	void Play(const Vec3& spawnPos, float radius, float endTime, SoundManager& sM)
	{
		position = spawnPos;
		explosionRadius = radius;
		endExplosionTimer = endTime;
		isActive = true;
		timer = 0.0f;
		sM.PlaySEAtPosition(RM().GetSound(ResourceKeys::Sound_Explosion),position);
	}

	void Update(float deltaTime);

	void Draw() const;

	const bool IsActive() const { return isActive; }

private:
	bool isActive{ false };
	float timer{ 0.0f };

	Vec3 position;
	float explosionRadius{ 1.0f };
	float endExplosionTimer{ 1.0f };
};

