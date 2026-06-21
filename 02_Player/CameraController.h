#pragma once
#include "DxLib.h"
#include "DxPlus.h"
#include "../07_Math/Vector3.h"
#include "../07_Math/DxConv.h"

class CameraController
{
public:
	CameraController() = default;

	void Reset(const Vec3& pos)
	{
		eye = pos;
		target = { 0.0f,0.0f,0.0f };
		up = { 0.0f,1.0f,0.0f };
	};

	//プレイヤーの位置・向きからカメラを更新する
	void UpdateFromPlayer(const Vec3& pos, float yaw, float pitch)
	{
		//カメラ位置 = プレイヤー位置
		eye = pos;

		//yaw/pitch から forward ベクトルを計算
		float cosPitch = std::cos(pitch);
		float sinPitch = std::sin(pitch);
		float cosYaw = std::cos(yaw);
		float sinYaw = std::sin(yaw);

		Vec3 forwerd{ cosYaw * cosPitch,sinPitch,sinYaw * cosPitch };

		//注視点 = 視点 + forward
		target = eye + forwerd;

		//カメラに反映
		SetCameraPositionAndTargetAndUpVec(DxConv::ToVECTOR(eye), DxConv::ToVECTOR(target), DxConv::ToVECTOR(up));
	};

	//レティクルの描画(十字)
	void ReticleDraw()const
	{
		//レティクルの表示位置(画面中央)
		int cx = DxPlus::CLIENT_WIDTH / 2;
		int cy = DxPlus::CLIENT_HEIGHT / 2;

		//線の長さ
		int size = 10;
		//線の太さ
		int thick = 5;
		//線の色(グレー)
		int color = GetColor(128, 128, 128);

		//線の描画(横)
		DrawLine(cx - size, cy, cx + size, cy, color, thick);
		//線の描画(縦)
		DrawLine(cx, cy - size, cx, cy + size, color, thick);
	}

private:
	//視点
	Vec3 eye{ 0.0f,0.0f,0.0f };
	//注視点
	Vec3 target{ 0.0f,0.0f,0.0f };
	//上方向
	Vec3 up{ 0.0f,1.0f,0.0f };
};

