#pragma once
#include "../DxPlus/DxPlus.h"

namespace Const
{
	//===== プレイヤー関連 =====
	//プレイヤーの半径
	constexpr float PLAYER_RADIUS{ 5.0f };
	//歩き中の移動速度
	constexpr float PLAYER_WALK_SPEED{ 200.0f };
	//ダッシュ中の移動速度
	constexpr float PLAYER_DASH_SPEED{ 500.0f };
	//ジャンプの高さ
	constexpr float PLAYER_JUMP_FORCE{ 1000.0f };
	//プレイヤーの視界の高さ
	constexpr float PLAYER_EYE_POSITION{ 70.0f };

	//===== カメラ関連 =====
	//カメラ感度
	constexpr float ROTATE_RAD_PAR_PIXEL{ DxPlus::PI * 2 / DxPlus::CLIENT_WIDTH };
	//下方向へのカメラ制限
	constexpr float PITC_MIN{ DxPlus::Deg2Rad * -89 };
	//上方向へのカメラ制限
	constexpr float PITC_MAX{ DxPlus::Deg2Rad * 89 };

	//===== 弾丸関連 =====
	//最大弾数
	constexpr int AMMO_MAX{ 16 };
	//弾速
	constexpr float BULLET_SPEED{ 2000.0f };
	//リロード時間
	constexpr float RELOAD_TIME{ 1.5f };

	//===== 敵関連 =====
	constexpr size_t MAX_ENEMY_COUNT{ 7 };
	const int ENEMY_LOW_MAXHP{ 3 };

	//===== 物理関連 =====
	constexpr float GRAVITY{ 2000.0f };

	//===== ゲーム内共通 =====
	constexpr int FPS_CAP = 480;
	constexpr float EPS = 1e-3f;

	//===== タレット関連 =====
	static constexpr int TURRET_COUNT = 4;
	static constexpr float TULLET_RELEASEDISTANCE = 200.0f;
	static constexpr float TULLET_SHOTRANGE = 2220.0f;
	static constexpr int ARROW_COUNT = 10;
}