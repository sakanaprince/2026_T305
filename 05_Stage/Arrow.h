#pragma once
#include "../07_Math/Vector3.h"
#include "../05_Stage/Stage.h"

class Turret;
class Arrow
{
public:
	Arrow() = default;
	~Arrow() = default;

	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;

	void LaunchArrow(Vec3 forward, float deltaTime, Turret& turret);

	bool IsActive() const { return isActive; }

private:
	int modelHandle{ -1 };

	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 scale{ 0.0f,0.0f,0.0f };
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	float speed{ 1000.0f };
	bool isActive{ false };
	float yaw{ 0.0f };

	float lifeTimer{ 0.0f };
	float lifeTime{ 2.0f };
};

