#include "Grid.h"
#include "DxLib.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"

void Grid::Draw() const
{
	DxLib::ClearDrawScreen();

	float size = halfCount * spacing;

	for (int i = -halfCount; i <= halfCount; i++) {
		const float x = i * spacing;
		const float y = i * spacing;
		const float z = i * spacing;
		int color = GetColor(255, 255, 255);

		DrawLine3D(DxConv::ToVECTOR({ -size, y, 0 }), DxConv::ToVECTOR({ size, y, 0 }), color);
		DrawLine3D(DxConv::ToVECTOR({ 0, -size, z }), DxConv::ToVECTOR({ 0, size, z }), color);
		DrawLine3D(DxConv::ToVECTOR({ x, 0, -size }), DxConv::ToVECTOR({ x, 0, size }), color);
	}

	// 3DÀ•WŽ²‚ð•`‰æ
	DxLib::DrawLine3D(DxConv::ToVECTOR({ 0, 0, 0 }), DxConv::ToVECTOR({ 500, 0, 0 }), GetColor(255, 0, 0));
	DxLib::DrawLine3D(DxConv::ToVECTOR({ 0, 0, 0 }), DxConv::ToVECTOR({ 0, 500, 0 }), GetColor(0, 255, 0));
	DxLib::DrawLine3D(DxConv::ToVECTOR({ 0, 0, 0 }), DxConv::ToVECTOR({ 0, 0, 500 }), GetColor(0, 0, 255));
}
