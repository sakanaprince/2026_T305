#include "EnemyRoot.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../08_Debug/DebugUI.h"

void EnemyRoot::Init()
{
	//-63, 2000 右の壁
	startPoints[0] = { -63, 0, 2000 };
	startPoints[1] = { -63, 0 , -2000 };

	//ゴール
	//startPoints[1] = { 0, 0, 0 };


	//動く版
	//rootPoints[0] = { 0, 0, 0 };
	//rootPoints[1] = { 0, 0, 200 };
	//rootPoints[2] = { -500, 0, 10 };
	//rootPoints[3] = { 0, 0, 0 };
}

void EnemyRoot::DebugDraw() const
{
	for (const auto& p : startPoints)
	{
		DrawSphere3D(DxConv::ToVECTOR(p), 50.0f, 16, GetColor(255, 0, 0), GetColor(255, 255, 0), true);
	}	
}

/// <summary>
/// 敵が複数のポイントを経由する時に使う。
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
[[nodiscard]]  Vec3 EnemyRoot::GetTargetPos(const size_t idx) const
{
	//size_tにマイナスはありえないので　p < 0　チェックはいらない
	//おかしな数字になるからね
	if (idx >= std::size(startPoints))
	{
		Debug().Log("EnemyRoot/GetTargetPosのIdxがおかしい",-1);
		DxPlus::Utils::FatalError(L"EnemyRoot : Idx ERROR");
		return { 0, -555, 0 };
	}

	if (std::size(startPoints) < 0)
	{
		Debug().Log("EnemyRootの要素数がおかしい", -1);
		DxPlus::Utils::FatalError(L"EnemyRoot : RootPoints Size ERROR");
		return { 0, -555, 0 };
	}

	//実体をContextに持たせたら無事に配列の中身が返ってきた。
	//EnemySpaawnerでEnemyRootの実体を持ってはいたが、initを呼んでは無かったから。
	//つまり初期化されていないこのクラスを参照していたのが原因だった。
	
	return startPoints[idx];
}

/// <summary>
///　開始地点を更新してから、敵のスポーン地点を返す
/// </summary>
/// <returns>敵のスポーン地点</returns>
Vec3 EnemyRoot::GetNextStartPos() 
{
	startIdx = startIdx + 1;

	if (startIdx == START_POINT_AMOUNT)
	{
		startIdx = 0;
	}

	return startPoints[startIdx];
}

