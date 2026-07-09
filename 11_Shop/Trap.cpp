#include "Trap.h"
#include "../04_Resource/ResourceKeys.h"
#include "../04_Resource/ResourceManager.h"
#include "../07_Math/DxConv.h"

void Trap::Reset(int _modelHandle, Vec3 _position)
{
	modelHandle = MV1DuplicateModel(_modelHandle);
	scale = { 2.0f,2.0f, 2.0f };
	hitScale = { 30.0f, 20.0f, 30.0f };
	position = _position;
	MV1SetScale(modelHandle, DxConv::ToVECTOR(scale));
	MV1SetPosition(modelHandle, DxConv::ToVECTOR(position));
}

void Trap::Draw() const
{
	MV1DrawModel(modelHandle);

#ifndef NDEBUG

	DrawCube3D(
		DxConv::ToVECTOR(position - hitScale),
		DxConv::ToVECTOR(position + hitScale),
		GetColor(255, 0, 0),
		GetColor(255, 0, 0),
		false);
#endif // !NDEBUG

}
