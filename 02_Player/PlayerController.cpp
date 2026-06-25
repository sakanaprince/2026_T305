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
	yaw = { 0.0f };
	pitch = { 0.0f };
	radius = { 5.0f };
	isGrounded = { true };
}

void PlayerController::Update(float deltaTime)
{
	//�}�E�X�̌��ݒn���擾
	GetMousePoint(&currentMouse.x, &currentMouse.y);

	//���E��]
	yaw -= (currentMouse.x - prevMouse.x) * Const::ROTATE_RAD_PAR_PIXEL;
	//�㉺��]
	pitch -= (currentMouse.y - prevMouse.y) * Const::ROTATE_RAD_PAR_PIXEL;

	//�㉺�̌����𐧌�
	pitch = std::clamp(pitch, Const::PITC_MIN, Const::PITC_MAX);

	//�}�E�X�̈ʒu�̍X�V
	prevMouse = currentMouse;

	//�v���C���[�̑O�����x�N�g��
	Vec3 forward{ cos(yaw),0.0f,sin(yaw) };
	//�v���C���[�̉E�����x�N�g��
	Vec3 right{ -forward.z,0.0f,forward.x };

	//�v���C���[�̕����A�_�b�V���̈ړ����x
	float playerSpeed = CheckHitKey(KEY_INPUT_LSHIFT) ? Const::PLAYER_DASH_SPEED : Const::PLAYER_WALK_SPEED;

	//�J�����̌����ɍ��킹��WASD�ړ�
	if (CheckHitKey(KEY_INPUT_W)) position += forward * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_S)) position -= forward * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_A)) position += right * playerSpeed * deltaTime;
	if (CheckHitKey(KEY_INPUT_D)) position -= right * playerSpeed * deltaTime;

	//�X�y�[�X�L�[�ŃW�����v
	if (CheckHitKey(KEY_INPUT_SPACE) && isGrounded) {
		velocity.y = Const::PLAYER_JUMP_FORCE;
		isGrounded = false;
	}

	//�d��
	velocity.y -= Const::GRAVITY * deltaTime;
	//�W�����v�����x
	position.y += velocity.y * deltaTime;

	//�X�e�[�W�̏��̍��W
	float groundY = stage.GetGroundHeight(position);

	//���̔���
	if (position.y <= groundY) {
		float diff = groundY - position.y;
		position.y += diff;
		velocity.y = 0.0f;
		isGrounded = true;
	}
	else {
		isGrounded = false;
	}

	//���_�̍����ɍX�V
	Vec3 eye = position + Vec3(0, Const::PLAYER_EYE_POSITION, 0);

	//�J�����̍X�V
	camera.UpdateFromPlayer(eye, yaw, pitch);
}

void PlayerController::Step(float deltaTime)
{
}

void PlayerController::Draw() const
{
	DrawCapsule3D(DxConv::ToVECTOR(position), { position.x, position.y + Const::PLAYER_EYE_POSITION, position.z }, 
		radius, 12, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

	//�J�����̃��e�B�N���̕`��
	camera.ReticleDraw();
}
