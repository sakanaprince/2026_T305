#pragma once
#include "../07_Math/Vector3.h"

class Stage
{
public:
	Stage() = default;
	~Stage() = default;

	void Init();
	void Reset();
	void Draw() const;

	float GetGroundHeight(const Vec3& pos) const;
	int GetModelHandle() const { return modelHandle; }

private:
	int modelHandle{ -1 };
	Vec3 scale{ 1.0f,1.0f,1.0f };
};

