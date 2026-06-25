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
	[[nodiscard]] size_t GetRootPointsLength() const { return std::size(rootPoints); }

private:
	std::array<Vec3, 5> rootPoints;
};

