#include "PlayerController.h"
#include "DxLib.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
}

void PlayerController::Reset()
{
	position = { 0.0f,0.0f,0.0f };
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

	//プレイヤーの前方向ベクトル
	Vec3 forward{ cos(yaw),0.0f,sin(yaw) };
	//プレイヤーの右方向ベクトル
	Vec3 right{ -forward.z,0.0f,forward.x };

	//プレイヤーの歩き、ダッシュの移動速度
	float playerSpeed = CheckHitKey(KEY_INPUT_LSHIFT) ? Const::PLAYER_DASH_SPEED : Const::PLAYER_WALK_SPEED;

	//カメラの向きに合わせたWASD移動
	if (CheckHitKey(KEY_INPUT_W)) position += forward * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_S)) position -= forward * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_A)) position += right * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_D)) position -= right * playerSpeed * deltaTime;

	Vec3 eye = position + Vec3(0, Const::PLAYER_EYE_POSITION, 0);

	//カメラの更新
	camera.UpdateFromPlayer(eye, yaw, pitch);
}

void PlayerController::Step(float deltaTime)
{
}

void PlayerController::Draw() const
{
	//カメラのレティクルの描画
	camera.ReticleDraw();
}
