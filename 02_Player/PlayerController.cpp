#include "PlayerController.h"
#include "DxLib.h"
#include "../10_Physics/Raycast.h"
#include "../99_Utility/Const.h"

void PlayerController::Init()
{
	gunFont = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_ANTIALIASING);
    reloadFont = CreateFontToHandle(NULL, 25, 2, DX_FONTTYPE_ANTIALIASING);
}

void PlayerController::Reset()
{
	position = { 0.0f,50.0f,0.0f };
	capsule = Capsule(position, Const::PLAYER_EYE_POSITION, Const::PLAYER_RADIUS);
	velocity = { 0.0f,0.0f,0.0f };
	forward = { 0.0f,0.0f,0.0f };
	right = { 0.0f,0.0f,0.0f };
	yaw = { 0.0f };
	pitch = { 0.0f };

	isGrounded = { true };
	isReload = { false };

    hp = { Const::PLAYER_MAX_HP };
    currentGunType = { 0 };

	reloadTimer = { Const::RELOAD_TIME };
	ammoCount = { Const::AMMO_MAX };
}

void PlayerController::Update(float deltaTime, Stage& stage)
{
	// �}�E�X�̌��ݒn���擾
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	// ���E�E�㉺��]
	yaw -= (currentMouse.x - prevMouse.x) * Const::ROTATE_RAD_PAR_PIXEL;
	pitch -= (currentMouse.y - prevMouse.y) * Const::ROTATE_RAD_PAR_PIXEL;
	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);
	prevMouse = currentMouse;

	// �v���C���[�̑O�E�E�����x�N�g��
	forward = { cos(yaw), 0.0f, sin(yaw) };
	right = { -forward.z, 0.0f, forward.x };

	float playerSpeed = CheckHitKey(KEY_INPUT_LSHIFT) ? Const::PLAYER_DASH_SPEED : Const::PLAYER_WALK_SPEED;

	// position�𒼐ړ��������A���̃t���[���́u���͂ɂ�鐅���ړ��x�N�g���v���v�Z����
	Vec3 moveVec = { 0.0f, 0.0f, 0.0f };
	if (CheckHitKey(KEY_INPUT_W)) moveVec += forward;
	if (CheckHitKey(KEY_INPUT_S)) moveVec -= forward;
	if (CheckHitKey(KEY_INPUT_A)) moveVec += right;
	if (CheckHitKey(KEY_INPUT_D)) moveVec += right;

	// �΂߈ړ��ł������Ȃ�Ȃ��悤�ɐ��K�����đ��x���|����
	if (moveVec.LengthSq() > Const::EPS) {
		moveVec = moveVec.Normalized() * playerSpeed;
	}

	// �X�y�[�X�L�[�ŃW�����v
	if (CheckHitKey(KEY_INPUT_SPACE) && isGrounded) {
		velocity.y = Const::PLAYER_JUMP_FORCE;
		isGrounded = false;
	}
    else if (!isGrounded) {
        velocity.y -= Const::GRAVITY * deltaTime;
    }

    Step(deltaTime, stage, moveVec);

	// ���_�̍����ɍX�V
	Vec3 eye = position + Vec3(0, Const::PLAYER_EYE_POSITION, 0);

	// �J�����̍X�V�i���n���Ă����������t���[�����s�����j
	camera.UpdateFromPlayer(eye, yaw, pitch);

	// �����[�h����
	if (!isReload && (CheckHitKey(KEY_INPUT_R) || ammoCount <= 0)) {
		isReload = true;
	}

	// �����[�h���̏���
	if (isReload) {
		reloadTimer -= deltaTime;
		if (reloadTimer <= 0.0f) {
			ammoCount = Const::AMMO_MAX;
			reloadTimer = Const::RELOAD_TIME;
			isReload = false;
		}
		return;
	}

    //�}�E�X�z�C�[���ŏe�̎�ނ̐؂�ւ�
    int wheelRot = GetMouseWheelRotVol();
    currentGunType += wheelRot;
    if (currentGunType < 0) currentGunType = 2;
    if (currentGunType > 2) currentGunType = 0;

	// �e�ۂ̔���
	static int prevMouseInput = 0;
	int nowMouse = GetMouseInput();
	bool leftDown = (nowMouse & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT);

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
	prevMouseInput = nowMouse;
}

void PlayerController::Step(float deltaTime, const class Stage& stage, const Vec3& moveVec)
{
    // ===== ���������̈ړ��ƕǔ��� =====
    constexpr int MAX_SLIDE_COUNT = 3;  // �ǂ̊p�Ő���܂Ŋ��点��
    constexpr float FLOOR_Y = 0.5f;     // ����ȏ�Ȃ珰�Ƃ��Ĉ���
    constexpr float SLIDE_UP_Y = 0.01f; // ������̊����ł������������l
    constexpr float STEP_LIMIT_HEIGHT = 1.5f; // ���z������i���̍���
    constexpr float SLOPE_LIMIT_HEIGHT = 0.7f;

    const int stageHandle = stage.GetModelHandle();

    // ���������̈ړ���
    Vec3 horizontal = moveVec * deltaTime;
    float moveLen = horizontal.Length();

    if (moveLen >= Const::EPS)
    {
        Vec3 dir = horizontal.Normalized();

        // �ǂɓ���������c��̈ړ���ǂɉ��������֊��点��
        for (int i = 0; i < MAX_SLIDE_COUNT && moveLen > Const::EPS; ++i)
        {
            // 2�{��Ray�̒��Łu��Ԏ�O�œ��������Փ˃f�[�^�v���L�^����ϐ�
            Physics::RayHit closestHit{};
            bool isHitAny = false;

            // �`�F�b�N����2�̍����i����: 5.0f / ��: ����菭�����j
            float rayHeights[] = { 5.0f, Const::PLAYER_EYE_POSITION - 5.0f };

            // 2�{��Ray�����[�v�Ŕ�΂�
            for (float h : rayHeights)
            {
                Vec3 start = position + Vec3::Up() * h;
                Vec3 end = start + dir * (moveLen + Const::PLAYER_STAGE_RADIUS);
                Physics::RayHit tempHit{};

                if (Physics::Raycast(stageHandle, start, end, tempHit))
                {
                    // �ŏ��ɓ��������A�܂��͂���܂ł̏Փ˂�����O�Ȃ�X�V
                    if (!isHitAny || tempHit.distance < closestHit.distance)
                    {
                        closestHit = tempHit;
                        isHitAny = true;
                    }
                }
            }

            // 1�{���������Ă��Ȃ��A�܂��͏������̖ʂȂ炻�̂܂ܐi��
            if (!isHitAny || closestHit.normal.y >= FLOOR_Y)
            {
                position += dir * moveLen;
                moveLen = 0.0f;
                break;
            }

            // ����ȍ~�̔���́A���́uhit�v���uclosestHit�v�ɒu�������邾��
            float allowed = closestHit.distance - Const::PLAYER_STAGE_RADIUS;
            allowed = std::clamp(allowed, 0.0f, moveLen);

            position += dir * allowed;
            moveLen -= allowed;

            if (moveLen <= Const::EPS)
            {
                moveLen = 0.0f;
                break;
            }

            // �c��̈ړ���ǂɉ��������֕ϊ�����
            Vec3 remain = dir * moveLen;
            Vec3 normal = closestHit.normal.Normalized();
            Vec3 slide = remain - normal * Vec3::Dot(remain, normal);

            // �s���R�ɏ�֓o�銊��͖h��
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

    // ���������̈ړ��Ə㉺����
    float dy = velocity.y * deltaTime;
    float nextY = position.y + dy;

    // �㏸���͓V��Ƃ̔�����s��
    if (dy > 0.0f)
    {
        isGrounded = false;

        Physics::RayHit hit{};
        Vec3 headPos = position + Vec3::Up() * Const::PLAYER_EYE_POSITION;

        // �V��ɓ���������A���̈ʒu�ŏ㏸���~�߂�
        if (Physics::RaycastUp(stage.GetModelHandle(), headPos, dy, hit))
        {
            position.y = hit.point.y - (Const::PLAYER_EYE_POSITION);
            velocity.y = 0.0f;
            return;
        }
    }

    // ���������̈ړ�
    position.y += dy;

    // RaycastDown �ŏ���T��
    Physics::RayHit hit{};
    Vec3 rayOrigin = position + Vec3::Up() * Const::PLAYER_EYE_POSITION;
    float rayLength = Const::PLAYER_EYE_POSITION + fabsf(dy) + 10.0f;

    if (Physics::RaycastDown(stage.GetModelHandle(), rayOrigin, rayLength, hit))
    {
        float groundY = hit.point.y;

        // ���̈ʒu������艺�Ȃ珰�ɌŒ�
        if (nextY <= groundY)
        {
            position.y = groundY;
            velocity.y = 0.0f;
            isGrounded = true;
        }
        else
        {
            position.y = nextY;
            isGrounded = false;
        }
    }
    else
    {
        // ����������Ȃ� �� ��
        position.y = nextY;
        isGrounded = false;
    }
}

void PlayerController::Draw() const
{
    //�v���C���[�̃X�e�[�W�Ƃ̓����蔻��̔��a
	DrawCylinder3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(position + Vec3(0, Const::PLAYER_EYE_POSITION, 0)),
		Const::PLAYER_STAGE_RADIUS, 12, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

    //�v���C���[�̓G�Ƃ̓����蔻��̔��a
    DrawCylinder3D(DxConv::ToVECTOR(position), DxConv::ToVECTOR(position + Vec3(0, Const::PLAYER_EYE_POSITION, 0)),
        Const::PLAYER_ENEMY_RADIUS, 12, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	//�J�����̃��e�B�N���̕`��
	camera.ReticleDraw();

	//�E���Ɏc�e���̕\��
	wchar_t buf[32];
	swprintf(buf, 32, L"%d/%d", ammoCount, Const::AMMO_MAX);
	int textWidth = GetDrawStringWidthToHandle(buf, wcslen(buf), gunFont);

	int x = DxPlus::CLIENT_WIDTH;
	int y = DxPlus::CLIENT_HEIGHT;

	DrawFormatStringToHandle(x - textWidth - 20, y - 60, GetColor(255, 255, 255), gunFont,
		L"%d/%d", GetAmmoCount(), Const::AMMO_MAX);

    //���݂̏e�̎�ނ�\��
    const wchar_t* gunName = L"";

    switch (currentGunType)
    {
    case GunType::Pistol:
        gunName = L"�n���h�K��";
        break;
    case GunType::Rifle:
        gunName = L"���C�t��";
        break;
    case GunType::Shotgun:
        gunName = L"�V���b�g�K��";
        break;
    }

    swprintf(buf, 32, L"%s", gunName);
    textWidth = GetDrawStringWidthToHandle(buf, wcslen(buf), gunFont);

    DrawFormatStringToHandle(x - textWidth - 10, y - 120, GetColor(255, 255, 255), gunFont, L"%s", gunName);

	//�����[�h���̕\��
	if (isReload) {
        DrawFormatStringToHandle(x / 2 - 55, y / 2 + 15, GetColor(255, 200, 0), reloadFont, L"RELOADING...");
	}
}