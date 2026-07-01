#pragma once
#include "DxLib.h"
#include "DxPlus.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"

class CameraController
{
public:
	CameraController() = default;

	const Vec3& GetEye() const { return eye; }
	const Vec3& GetTarget() const { return target; }
	const Vec3& GetUp() const { return up; }
	const Vec3& GetForward() const { return forward; }
	const Vec3& GetRight() const { return right; }

	void Reset(const Vec3& pos);

	//プレイヤーの位置・向きからカメラを更新する
	void UpdateFromPlayer(const Vec3& playerEye, float yaw, float pitch);

	//レティクルの描画(十字)
	void ReticleDraw()const;

private:
	//視点
	Vec3 eye{ 0.0f,0.0f,0.0f };
	//注視点
	Vec3 target{ 0.0f,0.0f,0.0f };
	//上方向
	Vec3 up{ 0.0f,1.0f,0.0f };
	//前方向
	Vec3 forward{ 0.0f,0.0f,0.0f };
	//右方向
	Vec3 right{ 0.0f,0.0f,0.0f };
};