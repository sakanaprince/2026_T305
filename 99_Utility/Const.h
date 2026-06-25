#pragma once

namespace Const
{
	//===== プレイヤー関連 =====
	//歩き中の移動速度
	constexpr float PLAYER_WALK_SPEED{ 400.0f };
	//ダッシュ中の移動速度
	constexpr float PLAYER_DASH_SPEED{ 700.0f };
	//ジャンプの高さ
	constexpr float PLAYER_JUMP_FORCE{ 1000.0f };
	//プレイヤーの視界の高さ
	constexpr float PLAYER_EYE_POSITION{ 100.0f };

	//===== カメラ関連 =====
	//カメラ感度
	constexpr float ROTATE_RAD_PAR_PIXEL{ DxPlus::PI * 2 / DxPlus::CLIENT_WIDTH };
	//下方向へのカメラ制限
	constexpr float PITC_MIN{ DxPlus::Deg2Rad * -89 };
	//上方向へのカメラ制限
	constexpr float PITC_MAX{ DxPlus::Deg2Rad * 89 };

	//===== 敵関連 =====

	//==== タレット関連
	static constexpr float TULLET_RELEASEDISTANCE = 100.0f;

	//===== 物理関連 =====
	constexpr float GRAVITY{ 2000.0f };

	//===== ゲーム内共通 =====
	constexpr int FPS_CAP = 480;
	constexpr float EPS = 1e-3f;
}