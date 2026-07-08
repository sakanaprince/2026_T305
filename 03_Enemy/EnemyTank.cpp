#include "EnemyTank.h"
#include "../99_Utility/Const.h"
#include "EnemySpawner.h"



void EnemyTank::Reset()
{
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	moveSpeed = 20.0f;
	rootTargetIndex = 0;
	currentHp = initHp;

	damageReactionTimer = 0.0f;
	isDamageReaction = false;
	killedReactionTimer = 0.0f;
	isKilledReaction = false;

	if (pEnemyRoot)
	{
		position = pEnemyRoot->GetNextStartPos_Ground();
		targetPosition = pEnemyRoot->GetCorePos();
		moveDir = (targetPosition - position).Normalized();
	}

	isAlive = true;
}

void EnemyTank::Draw() const
{
	if (!isAlive) { return; }

	Entity::Draw();
	
	explosion.Draw();
}

void EnemyTank::DrawDebug() const
{
	DrawSphere3D(DxConv::ToVECTOR(GetSphere().centerPos), hitSphereRadius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}

void EnemyTank::BodyLine() const
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
		sizeMagnification = 2.0f + damageReactionSize * (damageReactionTimer / DAMAGE_REACTION_TIME);
	}


	//中心の縦棒
	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x , (position.y + skin) , position.z }),
		DxConv::ToVECTOR({ position.x , (position.y + skin + height), position.z }),

		50 * sizeMagnification, 16, GetColor(10, 10, 50), GetColor(155, 155, 155), true
	);


	//position.yは固定
	constexpr float SPIN_RADIUS = 70.0f;
	constexpr float CAPSULE_RADIUS = 40.0f;
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
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(155, 100, 0), GetColor(255, 255, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x - sinSpin, position.y + height, position.z - cosSpin }),
		DxConv::ToVECTOR({ position.x, position.y + height, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(255, 25, 0), GetColor(255, 255, 0), true
	);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
