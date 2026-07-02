#pragma once
#include "../DxPlus/DxPlus.h"

namespace Const
{
	//===== プレイヤー関連 =====
	//プレイヤーの最大HP
	constexpr int PLAYER_MAX_HP{ 10 };
	//プレイヤーとステージとの当たり判定の半径
	constexpr float PLAYER_STAGE_RADIUS{ 130.0f };
	//プレイヤーと敵との当たり判定の半径
	constexpr float PLAYER_ENEMY_RADIUS{ 50.0f };
	//歩き中の移動速度
	constexpr float PLAYER_WALK_SPEED{ 200.0f };
	//ダッシュ中の移動速度
	constexpr float PLAYER_DASH_SPEED{ 500.0f };
	//ジャンプの高さ
	constexpr float PLAYER_JUMP_FORCE{ 1000.0f };
	//プレイヤーの視界の高さ
	constexpr float PLAYER_EYE_POSITION{ 80.0f };

	//===== カメラ関連 =====
	//カメラ感度
	constexpr float ROTATE_RAD_PAR_PIXEL{ DxPlus::PI * 2 / DxPlus::CLIENT_WIDTH };
	//下方向へのカメラ制限
	constexpr float PITC_MIN{ DxPlus::Deg2Rad * -89 };
	//上方向へのカメラ制限
	constexpr float PITC_MAX{ DxPlus::Deg2Rad * 89 };

	//===== 弾丸関連 =====
	//弾丸の表示上限
	constexpr int AMMO_MAX{ 30 };
	//ピストルの発射間隔
	constexpr float PISTOL_FIRE_INTERVAL{ 0.2 };
	//ライフルの発射間隔
	constexpr float RIFLE_FIRE_INTERVAL{ 0.05 };
	//ショットガンの発射間隔
	constexpr float SHOTGUN_FIRE_INTERVAL{ 0.5 };
	//ピストルのマガジン容量
	constexpr int PISTOL_MAGAZIN_MAX{ 16 };
	//ライフルのマガジン容量
	constexpr int RIFLE_MAGAZIN_MAX{ 30 };
	//ショットガンのマガジン容量
	constexpr int SHOTGUN_MAGAZIN_MAX{ 3 };
	//ピストルの弾丸一発分のダメージ
	constexpr int PISTOL_BULLET_DAMAGE{ 5 };
	//ライフルの弾丸一発分のダメージ
	constexpr int RIFLE_BULLET_DAMAGE{ 3 };
	//ショットガンの弾丸一発分のダメージ
	constexpr int SHOTGUN_BULLET_DAMAGE{ 2 };
	//弾速
	constexpr float BULLET_SPEED{ 4000.0f };
	//リロード時間
	constexpr float RELOAD_TIME{ 1.5f };

	//===== 敵関連 =====

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