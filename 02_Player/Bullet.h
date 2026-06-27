#pragma once
#include "../07_Math/Vector3.h"

class Bullet
{
private:
	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float radius{ 1.0f };
	float maxLife{ 2.0f };
	float life{ maxLife };
	bool isActive{ false };

public:
	const bool IsActive() const { return isActive; }

	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;
	void Fire(const Vec3& pos, const Vec3& dir);
};

