#include "EnemyLow.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../07_Math/Vector3.h"
#include "../DxPlus/DxPlus.h"

void EnemyLow::BodyLine() const
{
	//íÜêSÇÃècñ_
	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x, position.y + 250, position.z }),
		DxConv::ToVECTOR(position),
	
		50, 16, GetColor(255, 255, 255), GetColor(255, 0, 0), true
	);

	DxLib::DrawCapsule3D
	(
		//DxConv::ToVECTOR({ position.x + 250, position.y + 250, position.z }),
		DxConv::ToVECTOR({ position.x , position.y + 250, position.z + 250 }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0), GetColor(255, 0, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x - 250, position.y + 250, position.z }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0), GetColor(255, 0, 0), true
	);


	////íÜêSÇÃçúëgÇ›ìIÇ»
	//DxLib::DrawCapsule3D(
	//	DxConv::ToVECTOR({ position.x , position.y, position.z }),
	//	DxConv::ToVECTOR({ position.x - 250, position.y + 250, position.z - 50 }),
	//	50, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), true);

}



void EnemyLow::Update()
{
	animTimer += 0.1f;
}

void EnemyLow::Draw() const
{
	BodyLine();
}

void EnemyLow::DrawDebug() const
{
	const int division = 24;
	const unsigned int color = DxLib::GetColor(255, 255, 0);

	const float bottomY = position.y;//ë´å≥
	const float topY = position.y + height; //äÓèÄ+êgí∑

	//â~Çï`Ç≠èàóùÇÇ±Ç±Ç≈ã§í Ç…
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

		//â∫ÇÃâ~
		MyDrawCircle(bottom0, bottom1);
		//è„ÇÃâ~
		MyDrawCircle(top0, top1);
		//ècê¸
		if (i % 6 == 0) { MyDrawCircle(bottom0, top0); }
	}
}



