#pragma once
#include "../07_Math/Vector3.h"

class Gun
{
public:
	void Init();
	void Reset();
	void Update(float deltaTime);
	void Draw() const;

private:
	Vec3 position{ 0,0,0 };
	Vec3 scale{ 0,0,0 };

	int pistolModel{ -1 };
	int rifleModel{ -1 };
	int shotgunModel{ -1 };
};
