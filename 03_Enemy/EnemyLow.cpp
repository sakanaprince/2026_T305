#include "EnemyLow.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../07_Math/Vector3.h"
#include "../DxPlus/DxPlus.h"

void EnemyLow::BodyLine() const
{
	constexpr float skin = 70.0f;
	//中心の縦棒
	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x, position.y + skin, position.z }),
		DxConv::ToVECTOR({ position.x, position.y + height, position.z }),
	
		50, 16, GetColor(255, 255, 255), GetColor(255, 0, 0), true
	);

	//position.yは固定
	constexpr float RADIUS = 150;

	float sin_mul = std::sinf(animTimer);
	float cos_mul = std::cosf(animTimer);
	DxLib::DrawCapsule3D
	(
		//半分の2倍
		//( 0 ~ 50 - 25) * 1 = 25
		//( 0 ~ 50 - 25) * 2 =  50
		//-250 ~ 250　の値を使いたい、sinとかのぐるぐる巡回するやつで
		//sinとかcosは -1から1をぐるぐるするという性質を使って理想を表現している
		

		DxConv::ToVECTOR({ (position.x + RADIUS) * sin_mul, position.y + height, (position.z + RADIUS)*cos_mul }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0), GetColor(255, 0, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ (position.x - RADIUS) * sin_mul, position.y + height, (position.x - RADIUS) * cos_mul }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0), GetColor(255, 0, 0), true
	);


	////中心の骨組み的な
	//DxLib::DrawCapsule3D(
	//	DxConv::ToVECTOR({ position.x , position.y, position.z }),
	//	DxConv::ToVECTOR({ position.x - 250, position.y + 250, position.z - 50 }),
	//	50, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), true);

}



void EnemyLow::Update()
{
	animTimer += 0.05f;
}

void EnemyLow::Draw() const
{
	BodyLine();
}

void EnemyLow::DrawDebug() const
{
	const int division = 24;
	const unsigned int color = DxLib::GetColor(255, 255, 0);

	const float bottomY = position.y;//足元
	const float topY = position.y + height; //基準+身長

	//円を描く処理をここで共通に
	auto MyDrawCircle = [color](Vec3 a, Vec3 b)
		{
			DxLib::DrawLine3D(
				DxConv::ToVECTOR(a),
				DxConv::ToVECTOR(b),
				color
			);
		};

	for (int i = 0; i < division; ++i)
	{
		float angle0 = DX_PI_F * 2.0f * i / division;
		float angle1 = DX_PI_F * 2.0f * (i + 1) / division;

		Vec3 bottom0{
			position.x + std::sin(angle0) * radius,
			bottomY,
			position.z + std::cos(angle0) * radius
		};

		Vec3 bottom1{
		position.x + std::sin(angle1) * radius,
		bottomY,
		position.z + std::cos(angle1) * radius
		};

		Vec3 top0
		{
			bottom0.x,
			topY,
			bottom0.z
		};


		Vec3 top1
		{
			bottom1.x,
			topY,
			bottom1.z
		};

		//下の円
		MyDrawCircle(bottom0, bottom1);
		//上の円
		MyDrawCircle(top0, top1);
		//縦線
		if (i % 6 == 0) { MyDrawCircle(bottom0, top0); }
	}
}



