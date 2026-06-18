#include "EnemyLow.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../07_Math/Vector3.h"
#include "../DxPlus/DxPlus.h"

void EnemyLow::BodyLine() const
{
	//âÒÇÈÇ‚Ç¬
	DxLib::DrawCapsule3D(
		DxConv::ToVECTOR({
			std::sinf( (position.x - 50.0f) * animTimer * DxPlus::Deg2Rad) * 50,
			std::cosf( (position.z - 50.0f) * animTimer * DxPlus::Deg2Rad) * 50,
			position.z}),


		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0),GetColor(255,0,0), true);

	DxLib::DrawCapsule3D(
		DxConv::ToVECTOR({ position.x + 250, position.y + 250, position.z - 150 }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0), GetColor(255, 0, 0), true);


	//íÜêSÇÃçúëgÇ›ìIÇ»
	DxLib::DrawCapsule3D(
		DxConv::ToVECTOR({ position.x + 250, position.y + 250, position.z - 150 }),
		DxConv::ToVECTOR({ position.x - 50, position.y + 250, position.z - 50 }),
		50, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), true);

}



void EnemyLow::Update()
{
	animTimer += 0.1f;
}

void EnemyLow::Draw() const
{
	BodyLine();
}



