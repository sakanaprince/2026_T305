#include "PlayerController.h"
#include "DxLib.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
}

void PlayerController::Reset()
{
	position = { 0.0f,0.0f,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	forward = { 0.0f,0.0f,0.0f };
	right = { 0.0f,0.0f,0.0f };
	yaw = { 0.0f };
	pitch = { 0.0f };
	radius = { 5.0f };
	isGrounded = { true };
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
	forward = { cos(yaw),0.0f,sin(yaw) };
	//プレイヤーの右方向ベクトル
	right = { -forward.z,0.0f,forward.x };

	//プレイヤーの歩き、ダッシュの移動速度
	float playerSpeed = CheckHitKey(KEY_INPUT_LSHIFT) ? Const::PLAYER_DASH_SPEED : Const::PLAYER_WALK_SPEED;

	//カメラの向きに合わせたWASD移動
	if (CheckHitKey(KEY_INPUT_W)) position += forward * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_S)) position -= forward * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_A)) position += right * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_D)) position -= right * playerSpeed * deltaTime;

	//スペースキーでジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) && isGrounded) {
		velocity.y = Const::PLAYER_JUMP_FORCE;
		isGrounded = false;
	}

	//重力
	velocity.y -= Const::GRAVITY * deltaTime;
	//ジャンプ加速度
	position.y += velocity.y * deltaTime;

	//ステージの床の座標
	float groundY = stage.GetGroundHeight(position);

	//床の判定
	if (position.y <= groundY) {
		float diff = groundY - position.y;
		position.y += diff;
		velocity.y = 0.0f;
		isGrounded = true;
	}
	else {
		isGrounded = false;
	}

	//視点の高さに更新
	Vec3 eye = position + Vec3(0, Const::PLAYER_EYE_POSITION, 0);

	//カメラの更新
	camera.UpdateFromPlayer(eye, yaw, pitch);

	static int prevMouse = 0;
	int nowMouse = GetMouseInput();

	bool leftDown = (nowMouse & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT);

	if (leftDown) {
		for (int i = 0; i < Const::BULLET_COUNT; i++) {
			if (!bullets[i].IsActive()) {
				Vec3 pos = camera.GetEye() + camera.GetForward() * 20.0f;
				Vec3 dir = camera.GetForward();
				bullets[i].Fire(pos, dir);
				break;
			}
		}
	}

	prevMouse = nowMouse;
}

void PlayerController::Draw() const
{
	DrawCylinder3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(position + Vec3(0, Const::PLAYER_EYE_POSITION, 0)),
		radius, 12, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

	//カメラのレティクルの描画
	camera.ReticleDraw();
}