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
	//マウスの現在地を取得
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	//左右回転
	yaw -= (currentMouse.x - prevMouse.x) * Const::ROTATE_RAD_PAR_PIXEL;
	//上下回転
	pitch -= (currentMouse.y - prevMouse.y) * Const::ROTATE_RAD_PAR_PIXEL;

	//上下の向きを制限
	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);

	//マウスの位置の更新
	prevMouse = currentMouse;

	//プレイヤーの前方向
	Vec3 forwerd{ cos(yaw),0.0f,sin(yaw) };
	//プレイヤーの右方向
	Vec3 right{ -forwerd.z,0.0f,forwerd.x };

	//カメラの向きに合わせたWASD移動
	if (CheckHitKey(KEY_INPUT_W)) position += forwerd * Const::MOVE_SPEED * deltaTime;
	if (CheckHitKey(KEY_INPUT_S)) position -= forwerd * Const::MOVE_SPEED * deltaTime;
	if (CheckHitKey(KEY_INPUT_A)) position += right * Const::MOVE_SPEED * deltaTime;
	if (CheckHitKey(KEY_INPUT_D)) position -= right * Const::MOVE_SPEED * deltaTime;

	//カメラの更新
	camera.UpdateFromPlayer(position, yaw, pitch);
}

void PlayerController::Step(float deltaTime)
{
}

void PlayerController::Draw() const
{
	//カメラのレティクルの描画
	camera.ReticleDraw();
}
