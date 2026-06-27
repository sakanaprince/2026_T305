#pragma once
#include <array>
#include "../07_Math/Vector3.h"
//循環インクルードを防ぐためにdebugが使えない...なのでcppに書く

class EnemyRoot
{
public:
	EnemyRoot() = default;
	void Init();
	void DebugDraw() const;
	[[nodiscard]] Vec3 GetTargetPos(const size_t idx) const;
	[[nodiscard]] Vec3 GetNextStartPos();
	[[nodiscard]] const Vec3 GetCorePos() const { return corePos_kari; }
	[[nodiscard]] size_t GetRootPointsLength() const { return std::size(startPoints); }

private:
	static constexpr size_t START_POINT_AMOUNT = 2;
	std::array<Vec3, START_POINT_AMOUNT> startPoints;
	Vec3 corePos_kari{ 0,0,0 };

	size_t startIdx{ 0 };
};

