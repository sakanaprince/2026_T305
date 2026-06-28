#pragma once
#include "../07_Math/Vector3.h"
#include "../02_Player/PlayerController.h"
#include "../05_Stage/Arrow.h"
#include "../99_Utility/Const.h"
#include "../05_Stage/Stage.h"
#include "../03_Enemy/EnemyLow.h"
#include "../02_Player/Coin.h"

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

	void Init(PlayerController* _player, EnemyLow* _enemy, Coin* _coin);
	void Reset(Vec3 startPosition);
	void Update(float deltaTime);
	void BrokenUpdate();                    //タレットを解放していないときのUpdate
	void AvailableUpdate(float deltaTime);  //タレットを解放しているときのUpdate
	void Draw() const;

	void SetPosition(Vec3 pos) { position = pos; }
	Vec3 GetPosition() const { return position; }

	Vec3 GetScale() { return scale; }

	float GetYaw() const { return yaw; }

private:
	int modelTurret{ -1 };
	int modelBrokenTurret{ -1 };
	int modelNotArrowTurret{ -1 };
	int modelTurretHandle{ -1 };

	Vec3 scale{ 2.0f,2.0f,2.0f };
	Vec3 position{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	State state{ State::Broken };

	Arrow arrow[Const::ARROW_COUNT];

	float shotIntervalTimer{ 0.0f };
	float shotIntervalTime{ 2.0f };

	int turretCoin{ 100 };  //タレットの解放に必要なコインの数

	PlayerController* player{ nullptr };
	EnemyLow* enemy{ nullptr };
	Coin* coin{ nullptr };
};

