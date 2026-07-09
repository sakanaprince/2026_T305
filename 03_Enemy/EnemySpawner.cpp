#include "EnemySpawner.h"
#include "../01_Core/GameContext.h"
#include "../01_Core/EnemyDataMaster.h"

#include "../05_Stage/EnemyRoot.h"
#include "EnemyLow.h"
#include "EnemyQuick.h"
#include "EnemyTank.h"
#include "EnemyFly.h"

#include "../08_Debug/DebugUI.h"

#include <iterator>

void EnemySpawner::Init(EnemyRoot* enR, PlayerController* pc, GameContext* gC, EnemyDataMaster* eD)
{
	pGameContext = gC;
	enemyCollection.clear();
	enemyCollection.reserve(Const::MAX_ENEMY_COUNT);

	spawnedCount = 0;
	aliveEnemyCount = 0;
	pEnemyDataMaster = eD;


	currentWave = 0;
	waveSpawned = 0;
	maxWave = eD->GetEnemyWaveSize();

	gameStartLeftTime = pGameContext->GetLimit_Timer();
	//プール初期化
	for (int i = 0; i < Const::MAX_SAME_ENEMY_POOL_COUNT; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyLow>()); 
		
		enemyCollection[i]->BindEnemyDataMaster(eD);
		enemyCollection[i]->Init(enR, pc, EnemyKey::Low);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 2; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyQuick>());

		enemyCollection[i]->BindEnemyDataMaster(eD);
		enemyCollection[i]->Init(enR, pc, EnemyKey::Quick);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT * 2; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 3; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyTank>());

		enemyCollection[i]->BindEnemyDataMaster(eD);
		enemyCollection[i]->Init(enR, pc, EnemyKey::Tank);
		enemyCollection[i]->BindEnemySpawner(this);
	}
	//開始する値に注意
	for (int i = Const::MAX_SAME_ENEMY_POOL_COUNT * 3; i < Const::MAX_SAME_ENEMY_POOL_COUNT * 4; i++)
	{
		enemyCollection.push_back(std::make_unique<EnemyFly>());

		enemyCollection[i]->BindEnemyDataMaster(eD);
		enemyCollection[i]->Init(enR, pc, EnemyKey::Fly);
		enemyCollection[i]->BindEnemySpawner(this);
	}



}

void EnemySpawner::Reset()
{
	spawnedCount = 0;
	aliveEnemyCount = 0;
	currentWave = 0;
	waveSpawned = 0;

}


void EnemySpawner::Update(float deltaTime)
{
	spawnTimer += deltaTime;

	float firstTimer = spawnedCount * 0.1f;

	if (firstTimer > 4.0f)
	{
		firstTimer = 4.0f;
	}



	for (auto& e : enemyCollection)
	{
		

		if (!e->IsAlive()) { continue; }

		e->Update(deltaTime);
	}

	for (auto& e : enemyCollection)
	{


		if (!e->IsExplosionActive()) { continue; }

		e->ExplosionUpdate(deltaTime);
	}

	//全体攻撃のフラグが経ってるなら全体攻撃のタイマーを進める
	if (nowAllEnemyTakeDamage)
	{
		allEnemyTakeDamageDelayTimer -= deltaTime;

		if (allEnemyTakeDamageDelayTimer <= 0.0f)
		{
			nowAllEnemyTakeDamage = false;
			for (auto& e : enemyCollection)
			{
				if (!e->IsAlive()) { continue; }

				e->TakeDamage(allEnemyTakeDamageAmount);
			}
		}
	}

	if (currentWave >= maxWave) { return; }

	if (spawnTimer >= nextSpawnTime)
	{
		auto wave = pEnemyDataMaster->GetEnemyWave(currentWave);

		SpawnEnemy(wave->key);
		waveSpawned++;

		nextSpawnTime = wave->spawnDelay;
		if (waveSpawned >= wave->spawnCount)
		{
			currentWave++;
			waveSpawned = 0;
		}

		spawnTimer = 0;
	}
}

void EnemySpawner::Draw() const
{
	for (const auto& e : enemyCollection)
	{
		if (!e->IsAlive()) { continue; }

		e->Draw();
	}

	for (const auto& e : enemyCollection)
	{
		if (!e->IsExplosionActive()) { continue; }

		e->ExplosionDraw();
	}


	//ホーリー寿司の演出
	if (nowAllEnemyTakeDamage)
	{
		const int blendPower = 255 * (1 - allEnemyTakeDamageDelayTimer / allEnemyTakeDamageDelayTime);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendPower);
		DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH,DxPlus::CLIENT_HEIGHT }, GetColor(255, 255, 255)
			, true);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
#ifdef _DEBUG
	for (const auto& e : enemyCollection)
	{
		if (!e->IsAlive()) { continue; }

		e->DrawDebug();
	}
#endif
	

}


void EnemySpawner::DrawMiniMap() const
{
	//ミニマップ
	constexpr int left = DxPlus::CLIENT_WIDTH * 0.7f;
	constexpr int up = DxPlus::CLIENT_HEIGHT * 0.2f;
	constexpr int right = left + 700;
	constexpr int bottom = up + 700;
	constexpr int center_x = right - (right - left) * 0.5f;
	constexpr int center_y = bottom - (bottom - up) * 0.5f;

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	//背景でかい緑
	DxLib::DrawBox(left, up, right, bottom, GetColor(0, 128, 0), true);

	//飾りの線
	DxLib::DrawLine(center_x, up,   center_x, center_y, GetColor(16, 16, 16), 2);
	DxLib::DrawLine(left, center_y, center_x, center_y, GetColor(16, 16, 16), 2);
	DxLib::DrawLine(center_x, bottom, center_x, center_y, GetColor(16, 16, 16), 2);
	DxLib::DrawLine(right, center_y, center_x, center_y, GetColor(16, 16, 16), 2);

	constexpr float triangleSize = 32.0f;
	DxLib::DrawTriangle(center_x, center_y - triangleSize - 50.0f,
		center_x - triangleSize, center_y + 10, center_x + triangleSize, center_y + 10, GetColor(16, 16, 16), true);

	//コアの黒丸
	int coreX = right - (right - left) * 0.5f;
	int coreY = bottom - (bottom - up) * 0.5f;

	auto playerPos = pGameContext->GetPlayer().GetPosition();
	auto yaw = pGameContext->GetPlayer().GetYaw();

	//core描画
	{
		constexpr int coreSize = 64.0f;
		float dx = 0 - playerPos.x;
		float dz = 0 - playerPos.z;

		// 2. yaw（プレイヤーの向き）の「逆方向」に回転させる
		float offsetYaw = - yaw + (DX_PI_F / 2.0f);
		// プレイヤーが右を向いたら、世界は左に回る
		float rotatedX = dx * std::cos(offsetYaw) - dz * std::sin(offsetYaw);
		float rotatedZ = dx * std::sin(offsetYaw) + dz * std::cos(offsetYaw);
		DxLib::DrawCircle(
			coreX + rotatedX * 0.15f, coreY - rotatedZ * 0.1f,
			30.0f, GetColor(8, 8, 16), true);
	}

	//時間なかったのでプレイヤーの位置と向きに応じて変わる処理だけ書いてもらいました
	for (const auto& e : enemyCollection)
	{
		if (!e->IsAlive()) { continue; }

		VECTOR worldPos = DxConv::ToVECTOR(e->GetPosition());

	// 1. プレイヤーから見た「相対座標」を計算する
		float dx = worldPos.x - playerPos.x;
		float dz = worldPos.z - playerPos.z;

		// 2. yaw（プレイヤーの向き）の「逆方向」に回転させる
		float offsetYaw = -yaw + (DX_PI_F / 2.0f);
		// プレイヤーが右を向いたら、世界は左に回る
		float rotatedX = dx * std::cos(offsetYaw) - dz * std::sin(offsetYaw);
		float rotatedZ = dx * std::sin(offsetYaw) + dz * std::cos(offsetYaw);

		// 3. ミニマップの中心点をベースに、縮尺をかけて描画座標を決める
		// 2D画面のY軸は下がプラスなので、Zの変換時はマイナスにします
		float drawX = center_x + (rotatedX * 0.1f);
		float drawY = center_y - (rotatedZ * 0.1f);

		// 4. 計算した座標に描画する
		DxLib::DrawCircle(drawX, drawY, 20.0f, GetColor(255, 0, 0), true);

		/*DxLib::DrawCircle(
			center_x * std::cos(yaw) + worldPos.x * 0.15f,
			center_y * std::sin(yaw) - worldPos.z * 0.15f,
			20.0f, GetColor(255, 0, 0), true);*/

		//固定の位置と向きに対するアイコン表示
			//DxLib::DrawCircle(
	//	center_x + worldPos.x * 0.15f ,
	//	center_y - worldPos.z * 0.15f ,
	//	20.0f, GetColor(255, 0, 0), true);
	}
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

const void EnemySpawner::CoreDamage(int damage) const
{
	if (!pGameContext)
	{
		DxPlus::Utils::FatalError(L"Pointer GameContextがないバインド忘れてる by EnemySpaner");
	}

	//警告が気になるのでnull確認を明示
	if (pGameContext)
	{
		pGameContext->GetCore().TakeDamage(damage);
	}

}

const void EnemySpawner::MoneyInc(int money) const
{
	if (!pGameContext)
	{
		DxPlus::Utils::FatalError(L"Pointer GameContextがないバインド忘れてる EnemySpanerがいってる");
	}

	pGameContext->GetCoinManager().PlusCoin(money);
}

SoundManager& EnemySpawner::GetSoundManager()
{
	if (!pGameContext)
	{
		DxPlus::Utils::FatalError(L"Pointer GameContextがないバインド忘れてる EnemySpanerがいってる");
	}

	return pGameContext->GetSoundManager();
}

bool EnemySpawner::ReadyAllEnemyTakeDamage(int dmg, float delayTime)
{
	if (nowAllEnemyTakeDamage) { return false; }

	nowAllEnemyTakeDamage = true;
	allEnemyTakeDamageDelayTimer = delayTime;
	allEnemyTakeDamageDelayTime = delayTime;
	allEnemyTakeDamageAmount = dmg;
}


void EnemySpawner::PlaySoundPos(int handle, Vec3 pos)
{
	pGameContext->GetSoundManager().PlaySEAtPosition(handle, pos);
}

void EnemySpawner::EndGame()
{
	for (auto& e : enemyCollection)
	{
		e->EndGameDeActive();
	}
}

void EnemySpawner::SpawnEnemy(EnemyKey enName)
{
	//出現限界の数を超えてるならreturn
	if (aliveEnemyCount > Const::MAX_ENEMY_COUNT){	return; }

	//嗚呼今は基底クラスのEntityを召喚してしまっているのか（自力で解決済み makeUnique使えばよかった）

	//ENUMをあてにしてどうやって生成するクラスを変える？
	//そのために必要なのは全敵を管理しているenemyCollection配列に工夫が必要かも。
	//例えば 0から10番目まではLowで11番目から20番目まではQuickみたいな。(自力で解決済み この考察が当たっていた)
	

	size_t startIndex = 0;

	if		(enName == EnemyKey::Low){startIndex = 0;}
	else if (enName == EnemyKey::Quick){startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT;}
	else if (enName == EnemyKey::Tank) {startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT * 2;}
	else if (enName == EnemyKey::Fly) {startIndex = Const::MAX_SAME_ENEMY_POOL_COUNT * 3;}

	//待機状態の敵を探してResetする
	for (size_t i = startIndex; i < startIndex + Const::MAX_SAME_ENEMY_POOL_COUNT; i++)
	{
		if (enemyCollection[i]->IsAlive()) { continue; }

		spawnedCount++;
		aliveEnemyCount++;

		enemyCollection[i]->Reset();

		break;
	}
}


