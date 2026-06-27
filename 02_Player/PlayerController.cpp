#include "PlayerController.h"
#include "DxLib.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
	ammoFont = CreateFontToHandle(NULL, 48, 3, DX_FONTTYPE_ANTIALIASING);
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
	isReload = { false };
	reloadTimer = { Const::RELOAD_TIME };
	ammoCount = { Const::AMMO_MAX };
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

	//リロード(Rキーか弾数が0になったら)
	if (!isReload && (CheckHitKey(KEY_INPUT_R) || ammoCount <= 0)) {
		isReload = true;
	}

	//リロード中の処理
	if (isReload) {
		reloadTimer -= deltaTime;

		if (reloadTimer <= 0.0f) {
			ammoCount = Const::AMMO_MAX;
			reloadTimer = Const::RELOAD_TIME;
			isReload = false;
		}
		return;
	}

	//弾丸の発射
	static int prevMouse = 0;
	int nowMouse = GetMouseInput();

	bool leftDown = (nowMouse & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT);

	if (leftDown && ammoCount > 0) {
		for (int i = 0; i < Const::AMMO_MAX; i++) {
			if (!bullets[i].IsActive()) {
				Vec3 pos = camera.GetEye() + camera.GetForward() * 20.0f;
				Vec3 dir = camera.GetForward();
				ammoCount--;
				bullets[i].Fire(pos, dir);
				break;
			}
		}
	}
	prevMouse = nowMouse;
}

void PlayerController::Draw() const
{
	//プレイヤーの当たり判定
	DrawCylinder3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(position + Vec3(0, Const::PLAYER_EYE_POSITION, 0)),
		radius, 12, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

	//カメラのレティクルの描画
	camera.ReticleDraw();

	//右下に残弾数の表示
	wchar_t buf[32];
	swprintf(buf, 32, L"%d/%d", ammoCount, Const::AMMO_MAX);

	int textWidth = GetDrawStringWidthToHandle(buf, wcslen(buf), ammoFont);

	int x = DxPlus::CLIENT_WIDTH - textWidth - 20;
	int y = DxPlus::CLIENT_HEIGHT - 60;

	DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), ammoFont,
		L"%d/%d", GetAmmoCount(), Const::AMMO_MAX);

	//リロード中の表示
	if (isReload) {
		DrawString(DxPlus::CLIENT_WIDTH / 2 - 40, DxPlus::CLIENT_HEIGHT / 2 + 15, 
			L"RELOADING...", GetColor(255, 200, 0));
	}
}