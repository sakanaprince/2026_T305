#pragma once
#include "../07_Math/Vector3.h"
#include "../02_Player/PlayerController.h"
#include "../05_Stage/Arrow.h"
#include "../99_Utility/Const.h"
#include "../05_Stage/Stage.h"
#include "../03_Enemy/EnemySpawner.h"
#include "../02_Player/Coin.h"
#include "../12_Sound/SoundManager.h"

enum State
{
	Broken,    //タレットをまだ開放していない状態
	Available  //タレットを解放した状態
};

class GameContext;
class Turret
{
public:
	Turret() = default;
	~Turret() = default;

	void Init(PlayerController* _player, EnemySpawner* _enemySpawner, Coin* _coin, SoundManager* _sound);
	void Reset(Vec3 startPosition);
	void Update(float deltaTime);
	void AvailableUpdate(float deltaTime);  //タレットを解放しているときのUpdate
	void Draw() const;

	void SetPosition(Vec3 pos) { position = pos; }
	Vec3 GetPosition() const { return position; }

	Vec3 GetScale() { return scale; }

	float GetYaw() const { return yaw; }

	bool IsBroken() const { return state == State::Broken; }  //タレットが破壊されているかどうか

	Arrow& GetArrows(int i) { return arrows[i]; }  //指定された番号のArrowを返す

private:
	Vec3 GetNearbyEnemy();  //近くにいる敵を探す

	int modelTurret{ -1 };
	int modelBrokenTurret{ -1 };
	int modelNotArrowTurret{ -1 };
	int modelTurretHandle{ -1 };

	int spritePrice{ -1 };   //値段を表示する画像
	int spriteReleasePrice{ -1 };  //タレットを解放する前の画像
	int spriteUpgradePrice{ -1 };   //タレットのUpgradeの画像

	int soundArrowHandle{ -1 };

	Vec3 scale{ 2.0f,2.0f,2.0f };
	Vec3 position{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	State state{ State::Broken };

	Arrow arrows[Const::ARROW_COUNT];

	float shotIntervalTimer{ 0.0f };
	float shotIntervalTime{ 2.0f };
	float shotIntervalTime_Max{ 2.0f };
	float shotIntervalDownRate{ 0.2f };  //アップグレードしたときに何秒インターバルが減るかの数値

	float contactIntervalTimer{ 0.0f };
	float contactIntervalTime{ 0.5f };

	int turretCoin{ 100 };   //タレットの解放に必要なコインの数
	int turretUpgradeCoin{ 50 };  //タレットのアップグレードに必要なコインの数
	bool isPriceDraw{ false };  //値段を表示するかどうか

	PlayerController* player{ nullptr };
	EnemySpawner* enemySpawner{ nullptr };
	Coin* coin{ nullptr };
	SoundManager* sound{ nullptr };
};

