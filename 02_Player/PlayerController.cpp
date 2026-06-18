#include "PlayerController.h"
#include "DxLib.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
}

void PlayerController::Reset()
{
	position = { 600.0f,600.0f,-600.0f };
	camera.SetEye(position);
}

void PlayerController::Update(float deltaTime)
{
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	yaw -= (currentMouse.x - prevMouse.x) * Const::ROTATE_RAD_PAR_PIXEL;
	pitch -= (currentMouse.y - prevMouse.y) * Const::ROTATE_RAD_PAR_PIXEL;

	if (yaw > 2.0f * DxPlus::PI)
		yaw -= 2.0f * DxPlus::PI;
	if (yaw < 0.0f)
		yaw -= 2.0f * DxPlus::PI;

	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);

	prevMouse = currentMouse;

	camera.UpdateFromPlayer(position, yaw, pitch);
}

void PlayerController::Step(float deltaTime)
{
}

void PlayerController::Draw()
{
}
