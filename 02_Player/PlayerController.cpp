#include "PlayerController.h"
#include "DxLib.h"

void PlayerController::Init()
{
}

void PlayerController::Reset()
{
	position = { 0.0f,0.0f,0.0f };
	camera.SetEye(position);
}

void PlayerController::Update(float deltaTime)
{
}

void PlayerController::Step(float deltaTime)
{
}

void PlayerController::Draw()
{
}
