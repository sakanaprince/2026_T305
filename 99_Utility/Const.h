#pragma once
#include "../DxPlus/DxPlus.h"

namespace Const
{
	//===== プレイヤー関連 =====
	//プレイヤーの最大HP
	constexpr int PLAYER_MAX_HP{ 100 };
	//プレイヤーとステージとの当たり判定の半径
	constexpr float PLAYER_STAGE_RADIUS{ 130.0f };
	//プレイヤーと敵との当たり判定の半径
	constexpr float PLAYER_ENEMY_RADIUS{ 50.0f };
	//歩き中の移動速度
	constexpr float PLAYER_WALK_SPEED{ 300.0f };
	//ダッシュ中の移動速度
	constexpr float PLAYER_DASH_SPEED{ 500.0f };
	//エイム中の移動速度
	constexpr float PLAYER_AIM_SPEED{ 150.0f };
	//ジャンプの高さ
	constexpr float PLAYER_JUMP_FORCE{ 800.0f };
	//ジャンプの回数
	constexpr int MAX_JUNP_COUNT{ 2 };
	//リスポーンまでの時間
	constexpr int RESPAWN_TIME{ 5 };
	//プレイヤーの無敵時間
	constexpr float INVINCIBLE_TIME{ 1.0f };
	//プレイヤーの視界の高さ
	constexpr float PLAYER_EYE_POSITION{ 110.0f };

	//===== カメラ関連 =====
	//カメラ感度
	constexpr float ROTATE_RAD_PAR_PIXEL{ DxPlus::PI * 2 / DxPlus::CLIENT_WIDTH };
	//下方向へのカメラ制限
	constexpr float PITC_MIN{ DxPlus::Deg2Rad * -89 };
	//上方向へのカメラ制限
	constexpr float PITC_MAX{ DxPlus::Deg2Rad * 89 };

	//===== 弾丸関連 =====
	//弾丸の表示上限
	constexpr int AMMO_MAX{ 50 };
	//弾速
	constexpr float BULLET_SPEED{ 5000.0f };
	//リロード時間
	constexpr float RELOAD_TIME{ 1.0f };
	//エイム時の拡散倍率
	constexpr float AIM_SPREAD_RATE{ 0.3f };

	//ピストルの発射間隔
	constexpr float PISTOL_FIRE_INTERVAL{ 0.2f };
	//ピストルの拡散率
	constexpr float PISTOL_SPREAD_ANGLE{ 1.5f };
	//ピストルのマガジン容量
	constexpr int PISTOL_MAGAZIN_MAX{ 16 };
	//ピストルの弾丸一発分のダメージ
	constexpr int PISTOL_BULLET_DAMAGE{ 7 };

	//ライフルの発射間隔
	constexpr float RIFLE_FIRE_INTERVAL{ 0.1f };
	//ライフルの拡散率
	constexpr float RIFLE_SPREAD_ANGLE{ 3.0f };
	//ライフルのマガジン容量
	constexpr int RIFLE_MAGAZIN_MAX{ 30 };
	//ライフルの弾丸一発分のダメージ
	constexpr int RIFLE_BULLET_DAMAGE{ 3 };

	//ショットガンの発射間隔
	constexpr float SHOTGUN_FIRE_INTERVAL{ 0.8f };
	//ショットガンの拡散率
	constexpr float SHOTGUN_SPREAD_ANGLE{ 5.0f };
	//ショットガンのマガジン容量
	constexpr int SHOTGUN_MAGAZIN_MAX{ 3 };
	//ショットガンが一度に発射する弾数
	constexpr int SHOTGUN_PELLET_COUNT{ 10 };
	//ショットガンの弾丸一発分のダメージ
	constexpr int SHOTGUN_BULLET_DAMAGE{ 2 };

	//===== 敵関連 =====
	constexpr int ENEMY_LOW_MAXHP{ 3 };
	constexpr int MAX_ENEMY_COUNT{ 20 };
	constexpr int MAX_SAME_ENEMY_POOL_COUNT{ 10 };

	//===== 物理関連 =====
	constexpr float GRAVITY{ 2000.0f };

	//===== ゲーム内共通 =====
	constexpr int FPS_CAP = 480;
	constexpr float EPS = 1e-3f;

	//===== タレット関連 =====
	static constexpr int TURRET_COUNT = 4;
	static constexpr float TULLET_CONTACTDISTANCE = 200.0f;
	static constexpr float TULLET_SHOTRANGE = 2220.0f;
	static constexpr int ARROW_COUNT = 10;
}