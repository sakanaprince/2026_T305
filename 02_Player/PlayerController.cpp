#include "PlayerController.h"
#include "DxLib.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
}

void PlayerController::Reset()
{
	position = { 0.0f,100.0f,0.0f };
}

void PlayerController::Update(float deltaTime)
{
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	yaw -= (currentMouse.x - prevMouse.x) * Const::ROTATE_RAD_PAR_PIXEL;
	pitch -= (currentMouse.y - prevMouse.y) * Const::ROTATE_RAD_PAR_PIXEL;

	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);

	prevMouse = currentMouse;

	camera.UpdateFromPlayer(position, yaw, pitch);
}

void PlayerController::Step(float deltaTime)
{
}

void PlayerController::Draw() const
{
	camera.Draw();
}
