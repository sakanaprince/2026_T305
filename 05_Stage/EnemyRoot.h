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
	[[nodiscard]] Vec3 GetNextStartPos_Ground();
	[[nodiscard]] Vec3 GetNextStartPos_Sky();
	[[nodiscard]] const Vec3 GetCorePos() const { return corePos_kari; }
	[[nodiscard]] size_t GetRootPointsLength() const { return std::size(startPointsGround); }

private:
	Vec3 corePos_kari{ -110,0,-200 };


	static constexpr size_t GROUND_START_POINT_AMOUNT = 2;
	std::array<Vec3, GROUND_START_POINT_AMOUNT> startPointsGround;
	size_t startIdx_Ground{ 0 };


	static constexpr size_t SKY_START_POINT_AMOUNT = 2;
	std::array<Vec3, SKY_START_POINT_AMOUNT> startPointsSky;
	size_t startIdx_Sky{ 0 };
};

