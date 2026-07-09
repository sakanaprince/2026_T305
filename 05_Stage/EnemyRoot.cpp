#include "EnemyRoot.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../08_Debug/DebugUI.h"

void EnemyRoot::Init()
{
	//-63, 2000 右の壁
	startPointsGround[0] = { -63, 0,   2500 };
	startPointsGround[1] = { -63, 0 , -2500 };
	startPointsGround[2] = { -300, 0 ,-2500 };
	startPointsGround[3] = { 300, 0 , -2500 };


	startPointsSky[0] = { -2500, 400 ,  64 };
	startPointsSky[1] = {  2500, 400 , -64 };
	startPointsSky[2] = { -2500, 400 , -2500 };
	startPointsSky[3] = {  2500, 400 ,  2500 };
	startPointsSky[4] = {  2500, 400 , -2500 };
	startPointsSky[5] = { -2500, 400 ,  2500 };


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
	for (const auto& p : startPointsGround)
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
	if (idx >= std::size(startPointsGround))
	{
		Debug().Log("EnemyRoot/GetTargetPosのIdxがおかしい",-1);
		DxPlus::Utils::FatalError(L"EnemyRoot : Idx ERROR");
		return { 0, -555, 0 };
	}

	if (std::size(startPointsGround) < 0)
	{
		Debug().Log("EnemyRootの要素数がおかしい", -1);
		DxPlus::Utils::FatalError(L"EnemyRoot : RootPoints Size ERROR");
		return { 0, -555, 0 };
	}

	//実体をContextに持たせたら無事に配列の中身が返ってきた。
	//EnemySpaawnerでEnemyRootの実体を持ってはいたが、initを呼んでは無かったから。
	//つまり初期化されていないこのクラスを参照していたのが原因だった。
	
	return startPointsGround[idx];
}

/// <summary>
///　開始地点を更新してから、敵のスポーン地点を返す
/// </summary>
/// <returns>敵のスポーン地点</returns>
Vec3 EnemyRoot::GetNextStartPos_Ground()
{
	startIdx_Ground = startIdx_Ground + 1;

	if (startIdx_Ground == GROUND_START_POINT_AMOUNT)
	{
		startIdx_Ground = 0;
	}

	return startPointsGround[startIdx_Ground];
}

Vec3 EnemyRoot::GetNextStartPos_Sky()
{
	startIdx_Sky = startIdx_Sky + 1;

	if (startIdx_Sky== SKY_START_POINT_AMOUNT)
	{
		startIdx_Sky = 0;
	}

	return startPointsSky[startIdx_Sky];
}


