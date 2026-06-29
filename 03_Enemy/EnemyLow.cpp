#include "EnemyLow.h"
#include "DxLib.h"
#include "../07_Math/DxConv.h"
#include "../07_Math/Vector3.h"
#include "../DxPlus/DxPlus.h"

#include "../03_Enemy/EnemySpawner.h"
#include "../08_Debug/DebugUI.h"
void EnemyLow::BodyLine() const
{
	constexpr float skin = 30.0f;

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
		DxConv::ToVECTOR({ position.x , (position.y + height), position.z  }),
	
		50 * sizeMagnification, 16, GetColor(250, 250, 250), GetColor(255, 0, 0), true
	);


	//position.yは固定
	constexpr float SPIN_RADIUS = 50.0f;
	constexpr float CAPSULE_RADIUS = 20.0f;

	const float sinSpin = std::sinf(animTimer) * SPIN_RADIUS;
	const float cosSpin = std::cosf(animTimer) * SPIN_RADIUS;
	DxLib::DrawCapsule3D
	(
		//半分の2倍
		//( 0 ~ 50 - 25) * 1 = 25
		//( 0 ~ 50 - 25) * 2 =  50
		//-250 ~ 250　の値を使いたい、sinとかのぐるぐる巡回するやつで
		//sinとかcosは -1から1をぐるぐるするという性質を使って理想を表現している
		DxConv::ToVECTOR({ position.x +  sinSpin, position.y + height, position.z + cosSpin }),
		DxConv::ToVECTOR({position.x, position.y, position.z}),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(255, 255, 0), GetColor(0, 0, 0), true
	);

	DxLib::DrawCapsule3D
	(
		DxConv::ToVECTOR({ position.x - sinSpin, position.y + height, position.z - cosSpin }),
		DxConv::ToVECTOR(position),
		CAPSULE_RADIUS * sizeMagnification, 16, GetColor(255, 255, 0), GetColor(0, 0, 0), true
	);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	////中心の骨組み的な
	//DxLib::DrawCapsule3D(
	//	DxConv::ToVECTOR({ position.x , position.y, position.z }),
	//	DxConv::ToVECTOR({ position.x - 250, position.y + 250, position.z - 50 }),
	//	50, 16, GetColor(0, 255, 0), GetColor(255, 0, 0), true);

}

void EnemyLow::Init(EnemyRoot* enRoot)
{
	radius = 100.0f;
	height = 60.0f;
	isAlive = false;
	pEnemyRoot = enRoot;

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"null Ptr enemyRoot_p");
		return;
	}
}

void EnemyLow::Reset()
{
	moveDir = Vec3(0.0f, 0.0f, 0.0f);
	moveSpeed = 70.0f;
	rootTargetIndex = 0;
	currentHp = Const::ENEMY_LOW_MAXHP * 20;

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

void EnemyLow::Update(float deltaTime)
{
	if (!isAlive) { return; }

	if (!pEnemyRoot)
	{
		DxPlus::Utils::FatalError(L"Null Ptr");
		return;
	}

	if (isKilledReaction)
	{
		if (killedReactionTimer > 0.0f)
		{
			killedReactionTimer -= deltaTime;
			return;
		}

		isAlive = false;
	}

	if (isDamageReaction)
	{
		if (damageReactionTimer > 0.0f)
		{
			damageReactionTimer -= deltaTime;
			return;
		}

		isDamageReaction = false;
	}

	const float rootTargetPointDistance = (rootTargetPoint - position).Length();

	//目的ポイントに到達
	if (rootTargetPointDistance <= DISTANCE_LIMIT)
	{
		const size_t ROOT_ARRAY_SIZE = pEnemyRoot->GetRootPointsLength();

		rootTargetIndex = std::min(rootTargetIndex + 1, ROOT_ARRAY_SIZE);

		//目的ポイント == コア　だった時
		if(rootTargetIndex >= ROOT_ARRAY_SIZE)
		{
			isAlive = false;

			if(pEnemySpawner){ pEnemySpawner->DecAliveEnemyCount(); }

			return;
		}

		//目的ポイント != コア　だった時
		if (pEnemyRoot)
		{
			rootTargetPoint = pEnemyRoot->GetTargetPos(rootTargetIndex);

			//移動方向の更新
			moveDir = (rootTargetPoint - position).Normalized();
		}
	}

	position += moveDir * moveSpeed * deltaTime;

	animTimer += 10.0f * deltaTime;
}




void EnemyLow::Draw() const
{
	if (!isAlive) { return; }

	BodyLine();
}

void EnemyLow::DrawDebug() const
{
	
	if (!isAlive) { return; }

	const int division = 24;
	const unsigned int color = DxLib::GetColor(255, 255, 0);

	const float bottomY = position.y;//足元
	const float topY = position.y + height; //基準+身長

	//円を描く処理をここで共通に
	auto MyDrawCircle = [color](Vec3 a, Vec3 b)
		{
			DxLib::DrawLine3D(
				DxConv::ToVECTOR(a),
				DxConv::ToVECTOR(b),
				color
			);
		};

	for (int i = 0; i < division; ++i)
	{
		float angle0 = DX_PI_F * 2.0f * i / division;
		float angle1 = DX_PI_F * 2.0f * (i + 1) / division;

		Vec3 bottom0{
			position.x + std::sin(angle0) * radius,
			bottomY,
			position.z + std::cos(angle0) * radius
		};

		Vec3 bottom1{
		position.x + std::sin(angle1) * radius,
		bottomY,
		position.z + std::cos(angle1) * radius
		};

		Vec3 top0
		{
			bottom0.x,
			topY,
			bottom0.z
		};


		Vec3 top1
		{
			bottom1.x,
			topY,
			bottom1.z
		};

		//下の円
		MyDrawCircle(bottom0, bottom1);
		//上の円
		MyDrawCircle(top0, top1);
		//縦線
		if (i % 6 == 0) { MyDrawCircle(bottom0, top0); }
	}
	
}

void EnemyLow::TakeDamage(int amount)
{
	if (isKilledReaction) { return; }

	amount = std::max(amount, 0);
	currentHp = std::max(currentHp - amount, 0);

	damageReactionTimer = DAMAGE_REACTION_TIME;
	isDamageReaction = true;

	if(currentHp == 0 && !isKilledReaction)
	{
		isKilledReaction = true;
		killedReactionTimer = KILLED_REACTION_TIME;

		if (pEnemySpawner) { pEnemySpawner->DecAliveEnemyCount(); }
	}

}




