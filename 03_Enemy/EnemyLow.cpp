#include "EnemyLow.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../07_Math/Vector3.h"

void EnemyLow::BodyLine() const
{
	DrawCapsule3D(
		DxConv::ToVECTOR({ position.x -50, position.y + 250, position.z - 50 }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(255, 255, 0),GetColor(255,0,0), true);

	DrawCapsule3D(
		DxConv::ToVECTOR({ position.x + 250, position.y + 250, position.z - 150 }),
		DxConv::ToVECTOR(position),
		50, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), true);

	DrawCapsule3D(
		DxConv::ToVECTOR({ position.x + 250, position.y + 250, position.z - 150 }),
		DxConv::ToVECTOR({ position.x - 50, position.y + 250, position.z - 50 }),
		50, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), true);

}

void EnemyLow::Init()
{
	position = { 0,0,0 };
}

void EnemyLow::Update()
{

}

void EnemyLow::Draw() const
{
	BodyLine();
}
