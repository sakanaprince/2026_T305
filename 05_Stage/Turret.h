#pragma once
#include "../07_Math/Vector3.h"
#include "../02_Player/PlayerController.h"

enum State
{
	Broken,    //タレットをまだ開放していない状態
	Available  //タレットを解放した状態
};

class Turret
{
public:
	Turret() = default;
	~Turret() = default;

	void Init();
	void Reset(Vec3 startPosition);
	void Update(float deltaTime, PlayerController& player);
	void BrokenUpdate(PlayerController& player);                     //タレットを解放していないときのUpdate
	void AvailableUpdate(float deltaTime, PlayerController player);  //タレットを解放しているときのUpdate
	void Draw() const;

	void SetPos(Vec3 pos) { position = pos; }
	Vec3 GetPos() const { return position; }

private:
	int modelTurret{ -1 };
	int modelBrokenTurret{ -1 };
	int modelTurretHandle{ -1 };

	Vec3 scale{ 0.5f,0.5f,0.5f };
	Vec3 position{ 0.0f,0.0f,0.0f };
	float yaw{ 0.0f };
	State state{ State::Broken };
};

