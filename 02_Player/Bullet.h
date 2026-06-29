#pragma once
#include "../07_Math/Vector3.h"
#include "../10_Physics/Collision.h"

class Bullet
{
private:
	Collision::Sphere bullet{};
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float maxLife{ 2.0f };
	float life{ maxLife };
	bool isActive{ false };

public:
	const bool IsActive() const { return isActive; }
	void DeActivate() { isActive = false; }
	const Collision::Sphere GetRadius() const { return bullet; }

	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;
	void Fire(const Vec3& pos, const Vec3& dir);
};
