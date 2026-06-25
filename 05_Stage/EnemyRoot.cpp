#include "EnemyRoot.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../08_Debug/DebugUI.h"

void EnemyRoot::Init()
{
	rootPoints[0] = { 0, 0, 0 };
	rootPoints[1] = { 300, 0, 0 };
	rootPoints[2] = { 0, 0, 200 };
	rootPoints[3] = { -200, 0, 10 };
	rootPoints[4] = { 0, 0, 0 };
}

void EnemyRoot::DebugDraw() const
{
	for (const auto& p : rootPoints)
	{
		DrawSphere3D(DxConv::ToVECTOR(p), 50.0f, 16, GetColor(255, 0, 0), GetColor(255, 255, 0), true);
	}	
}

[[nodiscard]]  Vec3 EnemyRoot::GetTargetPos(const size_t idx) const
{
	//size_tにマイナスはありえないので　p < 0　チェックはいらない
	//おかしな数字になるからね
	if (idx >= std::size(rootPoints))
	{
		Debug().Log("EnemyRoot/GetTargetPosのIdxがおかしい",-1);
		DxPlus::Utils::FatalError(L"Idx ERROR");
		return { 0, -555, 0 };
	}

	if (std::size(rootPoints) < 0)
	{
		Debug().Log("EnemyRootの要素数がおかしい", -1);
		DxPlus::Utils::FatalError(L"Nu ERROR");
		return { 0, -555, 0 };
	}

	return rootPoints[idx];
}

