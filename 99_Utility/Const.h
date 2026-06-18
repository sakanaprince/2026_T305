#pragma once

namespace Const
{
	//===== プレイヤー関連 =====
	constexpr float PLAYER_EYE_POSITION{ 2.0f };

	//===== カメラ関連 =====
	constexpr float ROTATE_RAD_PAR_PIXEL{ DxPlus::PI * 2 / DxPlus::CLIENT_WIDTH };
	constexpr float PITC_MIN{ DxPlus::Deg2Rad * -89 };
	constexpr float PITC_MAX{ DxPlus::Deg2Rad * 89 };
	constexpr float MOVE_SPEED{ 400.0f };

	//===== 敵関連 =====

	//===== 物理関連 =====

	//===== ゲーム内共通 =====
	constexpr int FPS_CAP = 480;
	constexpr float EPS = 1e-3f;
}