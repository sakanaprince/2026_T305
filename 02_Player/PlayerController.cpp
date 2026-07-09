#include "PlayerController.h"
#include "DxLib.h"
#include "../10_Physics/Raycast.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
    deadFont= CreateFontToHandle(NULL, 70, 5, DX_FONTTYPE_ANTIALIASING);
	gunFont = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING);
    reloadFont = CreateFontToHandle(NULL, 25, 2, DX_FONTTYPE_ANTIALIASING);

    gun.Init();
}

void PlayerController::Reset()
{
	position = { 0.0f,0.0f,0.0f };
	velocity = { 0.0f,0.0f,0.0f };
	forward = { 0.0f,0.0f,0.0f };
	right = { 0.0f,0.0f,0.0f };
	yaw = { 0.0f };
	pitch = { 0.0f };

	isGrounded = { true };
    isAlive = { true };
    isAim = { false };
	isReload = { false };

    hp = { Const::PLAYER_MAX_HP };
    jumpCount = { 0 };

    invincibleTimer = { 0.0f };
    damageTimer = { 0.0f };
    respawnTimer = { Const::RESPAWN_TIME };
    fireTimer = { 0.0f };
    fireInterval = { Const::PISTOL_FIRE_INTERVAL };
	reloadTimer = { Const::RELOAD_TIME };

    currentGunType = { 0 };
	pistolAmmo = { Const::PISTOL_MAGAZIN_MAX };
	rifleAmmo = { Const::RIFLE_MAGAZIN_MAX };
	shotgunAmmo = { Const::SHOTGUN_MAGAZIN_MAX };

    gun.Reset();
}

void PlayerController::Update(float deltaTime, Stage& stage)
{
    if (!isAlive) {
        respawnTimer -= deltaTime;
        if (respawnTimer <= 0.0f) {
            respawnTimer = Const::RESPAWN_TIME;
            hp = Const::PLAYER_MAX_HP;
            position = { 0,0,0 };
            isAlive = false;
        }
        return;
    }

    if (hp <= 0) isAlive = false;

    if (damageTimer > 0.0f)
    {
        damageTimer -= deltaTime;
        if (damageTimer < 0.0f) damageTimer = 0.0f;
    }

    if (invincibleTimer > 0.0f) {
        invincibleTimer -= deltaTime;
        if (invincibleTimer < 0.0f) invincibleTimer = 0.0f;
    }

    static int prevMouseInput = 0;
    int nowMouse = GetMouseInput();
    static bool prevSpace = false;
    bool nowSpace = CheckHitKey(KEY_INPUT_SPACE);
    bool leftDown = (nowMouse & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT);

    //現在の銃の種類を取得
    currentGunType = gun.GetGunType();

	// マウスの現在地を取得
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	// 左右・上下回転
	yaw -= (currentMouse.x - prevMouse.x) * Const::ROTATE_RAD_PAR_PIXEL;
	pitch -= (currentMouse.y - prevMouse.y) * Const::ROTATE_RAD_PAR_PIXEL;
	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);
	prevMouse = currentMouse;

	// プレイヤーの前・右方向ベクトル
	forward = { cos(yaw), 0.0f, sin(yaw) };
	right = { -forward.z, 0.0f, forward.x };

	// positionを直接動かさず、このフレームの「入力による水平移動ベクトル」を計算する
	Vec3 moveVec = { 0.0f, 0.0f, 0.0f };
	if (CheckHitKey(KEY_INPUT_W)) moveVec += forward;
	if (CheckHitKey(KEY_INPUT_S)) moveVec -= forward;
	if (CheckHitKey(KEY_INPUT_A)) moveVec += right;
	if (CheckHitKey(KEY_INPUT_D)) moveVec -= right;

    float playerSpeed;

    if (isAim) playerSpeed = Const::PLAYER_AIM_SPEED;
    else if (CheckHitKey(KEY_INPUT_LSHIFT)) playerSpeed = Const::PLAYER_DASH_SPEED;
    else playerSpeed = Const::PLAYER_WALK_SPEED;

    isAim = nowMouse & MOUSE_INPUT_RIGHT;

	// 斜め移動でも速くならないように正規化して速度を掛ける
	if (moveVec.LengthSq() > Const::EPS) {
		moveVec = moveVec.Normalized() * playerSpeed;
	}

	// スペースキーでジャンプ
	if (nowSpace && !prevSpace) {
        if (jumpCount < Const::MAX_JUNP_COUNT) {
            velocity.y = Const::PLAYER_JUMP_FORCE;
            isGrounded = false;
            jumpCount++;
        }
	}
    
    if (!isGrounded) {
        velocity.y -= Const::GRAVITY * deltaTime;
    }

    prevSpace = nowSpace;

    Step(deltaTime, stage, moveVec);

	// 視点の高さに更新
	Vec3 eye = position + Vec3(0, Const::PLAYER_EYE_POSITION, 0);

	// カメラの更新
	camera.UpdateFromPlayer(eye, yaw, pitch, isAim);

    // 銃の種類の切り替え
    gun.Update(isReload);
    gun.UpdateFromCamera(position, camera.GetForward(), camera.GetRight(), camera.GetUp(), isAim);

	// リロード判定
    if (!isReload && (CheckHitKey(KEY_INPUT_R) || 
        pistolAmmo <= 0 || rifleAmmo <= 0 || shotgunAmmo <= 0)) {
        isReload = true;
    }

	// リロード中の処理
	if (isReload) {
		reloadTimer -= deltaTime;
		if (reloadTimer <= 0.0f) {
            switch (currentGunType)
            {
            case GunType::Pistol:
                pistolAmmo = Const::PISTOL_MAGAZIN_MAX;
                break;
            case GunType::Rifle:
                rifleAmmo = Const::RIFLE_MAGAZIN_MAX;
                break;
            case GunType::Shotgun:
                shotgunAmmo = Const::SHOTGUN_MAGAZIN_MAX;
                break;
            }
			reloadTimer = Const::RELOAD_TIME;
			isReload = false;
		}
		return;
	}

	// 弾丸の発射
    switch (currentGunType)
    {
    case GunType::Pistol:
        fireInterval = Const::PISTOL_FIRE_INTERVAL;
        break;
    case GunType::Rifle:
        fireInterval = Const::RIFLE_FIRE_INTERVAL;
        break;
    case GunType::Shotgun:
        fireInterval = Const::SHOTGUN_FIRE_INTERVAL;
        break;
    }

    fireTimer -= deltaTime;

	if (fireTimer <= 0.0f) {
        Vec3 eyePos = camera.GetEye();
        Vec3 forward = camera.GetForward();
        float spread = 0.0f;

        switch (currentGunType)
        {
        case GunType::Pistol:
            if (leftDown && pistolAmmo > 0)
            {
                spread = isAim ? Const::PISTOL_SPREAD_ANGLE * Const::AIM_SPREAD_RATE
                    : Const::PISTOL_SPREAD_ANGLE;

                Vec3 dir = RandomSpreadDirection(forward, spread);

                FireBullet(eyePos, dir);
                pistolAmmo--;
                fireTimer = fireInterval;
            }
            break;

        case GunType::Rifle:
            if ((nowMouse & MOUSE_INPUT_LEFT) && rifleAmmo > 0)
            {
                spread = isAim ? Const::RIFLE_SPREAD_ANGLE * Const::AIM_SPREAD_RATE
                    : Const::RIFLE_SPREAD_ANGLE;

                Vec3 dir = RandomSpreadDirection(forward, spread);

                FireBullet(eyePos, dir);
                rifleAmmo--;
                fireTimer = fireInterval;
            }
            break;

        case GunType::Shotgun:
            if (leftDown && shotgunAmmo > 0)
            {
                for (int n = 0; n < Const::SHOTGUN_PELLET_COUNT; n++)
                {
                    spread = isAim ? Const::SHOTGUN_SPREAD_ANGLE * Const::AIM_SPREAD_RATE
                        : Const::SHOTGUN_SPREAD_ANGLE;
                    Vec3 dir = RandomSpreadDirection(forward, spread);
                    FireBullet(eyePos, dir);
                }
                shotgunAmmo--;
                fireTimer = fireInterval;
            }
            break;
        }
	}
	prevMouseInput = nowMouse;
}

void PlayerController::Step(float deltaTime, Stage& stage, const Vec3& moveVec)
{
    // ===== 水平方向の移動と壁判定 =====
    constexpr int MAX_SLIDE_COUNT = 3;  // 壁の角で数回まで滑らせる
    constexpr float FLOOR_Y = 0.5f;     // これ以上なら床として扱う
    constexpr float SLIDE_UP_Y = 0.01f; // 上向きの滑りを打ち消すしきい値
    constexpr float STEP_LIMIT_HEIGHT = 1.5f; // 乗り越えられる段差の高さ
    constexpr float SLOPE_LIMIT_HEIGHT = 0.7f;

    const int stageHandle = stage.GetModelHandle();

    // 水平方向の移動量
    Vec3 horizontal = moveVec * deltaTime;
    float moveLen = horizontal.Length();

    if (moveLen >= Const::EPS)
    {
        Vec3 dir = horizontal.Normalized();

        // 壁に当たったら残りの移動を壁に沿う方向へ滑らせる
        for (int i = 0; i < MAX_SLIDE_COUNT && moveLen > Const::EPS; ++i)
        {
            // 2本のRayの中で「一番手前で当たった衝突データ」を記録する変数
            Physics::RayHit closestHit{};
            bool isHitAny = false;

            // チェックする2つの高さ（足元: 5.0f / 胸: 頭より少し下）
            float rayHeights[] = { 5.0f, Const::PLAYER_EYE_POSITION - 5.0f };

            // 2本のRayをループで飛ばす
            for (float h : rayHeights)
            {
                Vec3 start = position + Vec3::Up() * h;
                Vec3 end = start + dir * (moveLen + Const::PLAYER_STAGE_RADIUS);
                Physics::RayHit tempHit{};

                if (Physics::Raycast(stageHandle, start, end, tempHit))
                {
                    // 最初に当たった、またはこれまでの衝突よりも手前なら更新
                    if (!isHitAny || tempHit.distance < closestHit.distance)
                    {
                        closestHit = tempHit;
                        isHitAny = true;
                    }
                }
            }

            // 1本も当たっていない、または床扱いの面ならそのまま進む
            if (!isHitAny || closestHit.normal.y >= FLOOR_Y)
            {
                position += dir * moveLen;
                moveLen = 0.0f;
                break;
            }

            // これ以降の判定は、元の「hit」を「closestHit」に置き換えるだけ
            float allowed = closestHit.distance - Const::PLAYER_STAGE_RADIUS;
            allowed = std::clamp(allowed, 0.0f, moveLen);

            position += dir * allowed;
            moveLen -= allowed;

            if (moveLen <= Const::EPS)
            {
                moveLen = 0.0f;
                break;
            }

            // 残りの移動を壁に沿う方向へ変換する
            Vec3 remain = dir * moveLen;
            Vec3 normal = closestHit.normal.Normalized();
            Vec3 slide = remain - normal * Vec3::Dot(remain, normal);

            // 不自然に上へ登る滑りは防ぐ
            if (slide.y >= SLIDE_UP_Y)
            {
                slide.y = 0.0f;
            }
            float slideLen = slide.Length();

            if (slideLen <= Const::EPS)
            {
                moveLen = 0.0f;
                break;
            }

            dir = slide / slideLen;
            moveLen = slideLen;
        }
    }

    // 垂直方向の移動と上下判定
    float dy = velocity.y * deltaTime;
    float nextY = position.y + dy;

    // 上昇中は天井との判定を行う
    if (dy > 0.0f)
    {
        isGrounded = false;

        Physics::RayHit hit{};
        Vec3 headPos = position + Vec3::Up() * Const::PLAYER_EYE_POSITION;

        // 天井に当たったら、その位置で上昇を止める
        if (Physics::RaycastUp(stage.GetModelHandle(), headPos, dy, hit))
        {
            position.y = hit.point.y - (Const::PLAYER_EYE_POSITION);
            velocity.y = 0.0f;
            return;
        }
    }

    // 垂直方向の移動
    position.y += dy;

    // RaycastDown で床を探す
    Physics::RayHit hit{};
    Vec3 rayOrigin = position + Vec3::Up() * Const::PLAYER_EYE_POSITION;
    float rayLength = Const::PLAYER_EYE_POSITION + fabsf(dy) + 10.0f;

    if (Physics::RaycastDown(stage.GetModelHandle(), rayOrigin, rayLength, hit))
    {
        float groundY = hit.point.y;

        // 次の位置が床より下なら床に固定
        if (nextY <= groundY)
        {
            position.y = groundY;
            velocity.y = 0.0f;
            isGrounded = true;
            jumpCount = 0;
        }
        else
        {
            position.y = nextY;
            isGrounded = false;
        }
    }
    else
    {
        // 床が見つからない → 空中
        position.y = nextY;
        isGrounded = false;
    }
}

void PlayerController::Draw() const
{
 //   //プレイヤーのステージとの当たり判定の半径
	//DrawCylinder3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(position + Vec3(0, Const::PLAYER_EYE_POSITION, 0)),
	//	Const::PLAYER_STAGE_RADIUS, 12, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

 //   //プレイヤーの敵との当たり判定の半径
 //   DrawCylinder3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(position + Vec3(0, Const::PLAYER_EYE_POSITION, 0)),
 //       Const::PLAYER_ENEMY_RADIUS, 12, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	//カメラのレティクルの描画
	camera.ReticleDraw();

    gun.Draw();

    //現在の銃の種類を表示
    const wchar_t* gunName = L"";
    wchar_t ammoBuf[32];

    switch (currentGunType)
    {
    case GunType::Pistol:
        gunName = L"ハンドガン";
        swprintf(ammoBuf, 32, L"%d/%d", pistolAmmo, Const::PISTOL_MAGAZIN_MAX);
        break;

    case GunType::Rifle:
        gunName = L"ライフル";
        swprintf(ammoBuf, 32, L"%d/%d", rifleAmmo, Const::RIFLE_MAGAZIN_MAX);
        break;

    case GunType::Shotgun:
        gunName = L"ショットガン";
        swprintf(ammoBuf, 32, L"%d/%d", shotgunAmmo, Const::SHOTGUN_MAGAZIN_MAX);
        break;
    }

    //右下に残弾数の表示
	wchar_t buf[32];
	swprintf(buf, 32, L"%s", ammoBuf);
	int textWidth = GetDrawStringWidthToHandle(buf, wcslen(buf), gunFont);

	int x = DxPlus::CLIENT_WIDTH;
	int y = DxPlus::CLIENT_HEIGHT;

	DrawFormatStringToHandle(x - textWidth - 20, y - 60, GetColor(255, 255, 255),
        gunFont, L"%s", ammoBuf);

    //銃の種類を表示
    swprintf(buf, 32, L"%s", gunName);
    textWidth = GetDrawStringWidthToHandle(buf, wcslen(buf), gunFont);

    DrawFormatStringToHandle(x - textWidth - 10, y - 120, GetColor(255, 255, 255), gunFont, L"%s", gunName);

    DrawFormatString(x, y, GetColor(255, 255, 255), L"HP: %d / %d", hp, Const::PLAYER_MAX_HP);

    //���S���̕\��
    if (!isAlive) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 110);
        DrawBox(0, 0, x, y, GetColor(255, 0, 0), TRUE);

        DrawFormatStringToHandle(x / 2 - 130, y / 2 - 300, GetColor(255, 255, 255), deadFont, L"�����܂�");
        DrawFormatStringToHandle(x / 2 - 20, y / 2 - 200, GetColor(255, 255, 255),
            deadFont, L"%d", (int)respawnTimer);
    }

	//リロード中の表示
	if (isReload) {
        DrawFormatStringToHandle(x / 2 - 55, y / 2 + 15, GetColor(255, 200, 0), reloadFont, L"RELOADING...");
	}

    //�_���[�W���o
    if (damageTimer > 0.0f)
    {
        float alphaRate = damageTimer / 0.2f;
        int alpha = (int)(alphaRate * 150);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawBox(0, 0, x, y, GetColor(255, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

void PlayerController::TakeDamage(const int damage)
{
    if (invincibleTimer > 0.0f) return;

    hp -= damage;
    damageTimer = 0.2f;
    invincibleTimer = Const::INVINCIBLE_TIME;
}

void PlayerController::FireBullet(const Vec3& eye, const Vec3& forward)
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (!bullets[i].IsActive())
        {
            Vec3 pos = eye + forward * 20.0f;
            bullets[i].Fire(pos, forward);
            break;
        }
    }
}

Vec3 PlayerController::RandomSpreadDirection(const Vec3& forward, float spreadDeg)
{
    // ランダム角度
    float yawOffset = (GetRand(2000) / 1000.0f - 1.0f) * spreadDeg;
    float pitchOffset = (GetRand(2000) / 1000.0f - 1.0f) * spreadDeg;

    float yawRad = yawOffset * DX_PI / 180.0f;
    float pitchRad = pitchOffset * DX_PI / 180.0f;

    // forward を回転させる
    Vec3 dir = forward;

    // yaw 回転
    float cy = cos(yawRad);
    float sy = sin(yawRad);
    dir = { dir.x * cy - dir.z * sy, dir.y, dir.x * sy + dir.z * cy };

    // pitch 回転
    float cp = cos(pitchRad);
    float sp = sin(pitchRad);
    dir = { dir.x, dir.y * cp - dir.z * sp, dir.y * sp + dir.z * cp };

    return dir.Normalized();
}
