#pragma once
#include "../07_Math/Vector3.h"

class Bullet
{
private:
	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float radius{ 5.0f };
	bool isActive{ false };

public:
	void Init();
	void Reset();
	void Update();
	void Draw() const;
};

