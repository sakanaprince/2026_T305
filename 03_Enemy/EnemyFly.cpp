#include "EnemyFly.h"
#include "../99_Utility/Const.h"
#include "EnemySpawner.h"


void EnemyFly::Reset()
{
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	moveSpeed = 400.0f;
	rootTargetIndex = 0;
	currentHp = initHp;
	hitSphereRadius = 120.0f;
	damageReactionTimer = 0.0f;
	isDamageReaction = false;
	killedReactionTimer = 0.0f;
	isKilledReaction = false;
	gravity = 0.0f;
	if (pEnemyRoot)
	{
		position = pEnemyRoot->GetNextStartPos_Sky();
		const float flyStartPosY = 500.0f;
		position.y += flyStartPosY;
		targetPosition = pEnemyRoot->GetCorePos();
		moveDir = (targetPosition - position).Normalized();
	}

	isAlive = true;
}

void EnemyFly::Update(float deltaTime)
{
	if (isKilledReaction)
	{
		position.y -= gravity; 
		gravity += 50.0f * deltaTime;

		if (position.y < 0.0f)
		{
			explosion.Play({position.x, 0.0f, position.z}, 600.0f, 0.4f, pEnemySpawner->GetSoundManager());

			isAlive = false;
		}
		return;
	}


	Entity::Update(deltaTime);
}


void EnemyFly::DrawDebug() const
{
	DrawSphere3D(DxConv::ToVECTOR(GetSphere().centerPos), hitSphereRadius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}

void EnemyFly::StepGround(float deltaTime)
{
	Entity::StepGround(deltaTime);
}

void EnemyFly::ExplosionUpdate(float deltaTime)
{
	explosion.Update(deltaTime);
}

void EnemyFly::ExplosionDraw() const
{
	explosion.Draw();
}



void EnemyFly::BodyLine() const
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

		50 * sizeMagnification, 16, GetColor(0, 155, 20), GetColor(255, 255, 255), true
	);

	//position.yは固定
	constexpr float SPIN_RADIUS = 170.0f;
	constexpr float CAPSULE_RADIUS = 10.0f;
	constexpr float spinSpeedBoost = 18.0f;

	const float sinSpin = std::sinf(animTimer * spinSpeedBoost) * SPIN_RADIUS;
	const float cosSpin = std::cosf(animTimer * spinSpeedBoost) * SPIN_RADIUS;

	const float PropellerHeight = height * 2;
	DxLib::DrawCapsule3D
	(
		//半分の2倍
		//( 0 ~ 50 - 25) * 1 = 25
		//( 0 ~ 50 - 25) * 2 =  50
		//-250 ~ 250　の値を使いたい、sinとかのぐるぐる巡回するやつで
		//sinとかcosは -1から1をぐるぐるするという性質を使って理想を表現している
		DxConv::ToVECTOR({ position.x + sinSpin, position.y + PropellerHeight, position.z + cosSpin }),
		DxConv::ToVECTOR({ position.x, position.y + PropellerHeight, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(10, 100, 0), GetColor(255, 255, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x - sinSpin, position.y + PropellerHeight, position.z - cosSpin }),
		DxConv::ToVECTOR({ position.x, position.y + PropellerHeight, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(0, 155, 0), GetColor(255, 255, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x - cosSpin, position.y + PropellerHeight, position.z - sinSpin }),
		DxConv::ToVECTOR({ position.x, position.y + PropellerHeight, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(0, 155, 0), GetColor(255, 255, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x + cosSpin, position.y + PropellerHeight, position.z + sinSpin }),
		DxConv::ToVECTOR({ position.x, position.y + PropellerHeight, position.z }),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(0, 155, 0), GetColor(255, 255, 0), true
	);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
