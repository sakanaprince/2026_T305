#include "EnemyQuick.h"
#include "../99_Utility/Const.h"
#include "EnemySpawner.h"

void EnemyQuick::Init(EnemyRoot* enRoot, PlayerController* pc)
{
	radius = 80.0f;
	height = 40.0f;
	isAlive = false;
	pEnemyRoot = enRoot;
	pPlayer = pc;

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"null Ptr enemyRoot_p");
		return;
	}
}

void EnemyQuick::Reset()
{
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	moveSpeed = 300.0f;
	rootTargetIndex = 0;
	currentHp = initHp;

	damageReactionTimer = 0.0f;
	isDamageReaction = false;
	killedReactionTimer = 0.0f;
	isKilledReaction = false;

	if (pEnemyRoot)
	{
		position = pEnemyRoot->GetNextStartPos();
		rootTargetPoint = pEnemyRoot->GetCorePos();
		moveDir = (rootTargetPoint - position).Normalized();
	}

	isAlive = true;
}

void EnemyQuick::Update(float deltaTime)
{
	if (!isAlive) { return; }

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"EnemyRoot Null Ptr by Quick");
		return;
	}

	if (isKilledReaction)
	{
		KilledReactionUpdate(deltaTime);
		explosion.Update(deltaTime);
		return;
	}

	if (isDamageReaction)
	{
		DamageReactionUpdate(deltaTime);
		return;
	}

	StepGround(deltaTime);

	animTimer += 10.0f * deltaTime;
}

void EnemyQuick::Draw() const
{
	if (!isAlive) { return; }

	BodyLine();
	explosion.Draw();
}

void EnemyQuick::DrawDebug() const
{
	DrawSphere3D( DxConv::ToVECTOR(GetSphere().centerPos), radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}


void EnemyQuick::BodyLine() const
{


	float sizeMagnification = 1.0f;

	if (isKilledReaction)
	{
		sizeMagnification = killedReactionTimer / KILLED_REACTION_TIME;
	}
	else if (isDamageReaction)
	{
		DxLib::SetDrawBlendMode(DX_BLENDMODE_MUL, 64);
		//1スタート0になっていく
		constexpr float damageReactionSize = 1.1f;
		sizeMagnification = 1.0f + damageReactionSize * (damageReactionTimer / DAMAGE_REACTION_TIME);
	}


	//中心の縦棒
	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x , (position.y + skin) , position.z }),
		DxConv::ToVECTOR({ position.x , (position.y + skin + height), position.z }),

		50 * sizeMagnification, 16, GetColor(0, 0, 250), GetColor(0, 0, 255), true
	);


	//position.yは固定
	constexpr float SPIN_RADIUS = 50.0f;
	constexpr float CAPSULE_RADIUS = 20.0f;
	constexpr float spinSpeedBoost = 3.0f;

	const float sinSpin = std::sinf(animTimer * spinSpeedBoost) * SPIN_RADIUS;
	const float cosSpin = std::cosf(animTimer * spinSpeedBoost) * SPIN_RADIUS;

	DxLib::DrawCapsule3D
	(
		//半分の2倍
		//( 0 ~ 50 - 25) * 1 = 25
		//( 0 ~ 50 - 25) * 2 =  50
		//-250 ~ 250　の値を使いたい、sinとかのぐるぐる巡回するやつで
		//sinとかcosは -1から1をぐるぐるするという性質を使って理想を表現している
		DxConv::ToVECTOR({ position.x + sinSpin, position.y + height, position.z + cosSpin }),
		DxConv::ToVECTOR({ position.x, position.y + height, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(255, 255, 0), GetColor(0, 0, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x - sinSpin, position.y + height, position.z - cosSpin }),
		DxConv::ToVECTOR({ position.x, position.y + height, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(255, 255, 0), GetColor(0, 0, 0), true
	);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
