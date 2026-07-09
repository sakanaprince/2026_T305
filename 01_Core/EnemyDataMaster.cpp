#include "EnemyDataMaster.h"


#include <fstream>
#include "../DxPlus/DxPlus.h"

void EnemyDataMaster::LoadJson()
{
    //インクルードできず40分経ったので仕方なくGemini使いました(あとは自力)
    //理由はヘッダーだけでいいのに余計なファイルいれていたから
    using json = nlohmann::json;

    {
        std::ifstream file_enemyData("Data/EnemyData.json");

        if (!file_enemyData.is_open()) {

            DxPlus::Utils::FatalError(L"読み込めなかったjson");
            return;
        }

        // 2. ファイルの中身を丸ごとJSONオブジェクトにパース（解析）する
        json data;
        file_enemyData >> data;

        // 3. JSONの配列（"enemies"）をループで回して、構造体に割り当てていく
        for (const auto& enemyJson : data["enemies"]) {
            auto enemy = std::make_shared<EnemyStatus>();

            // json["キー名"] で型を自動判別して代入してくれる（超便利！）
            enemy->key = enemyJson["key"];
            enemy->maxHp = enemyJson["maxHp"];
            enemy->moveSpeed = enemyJson["moveSpeed"];
            enemy->coreDamage = enemyJson["coreDamage"];
            enemy->dropCoin = enemyJson["dropCoin"];

            // データベース（Map）に登録
            enemyAllData[enemy->key] = enemy;
        }
    }

    //wave読み込み
    std::ifstream file_enemyWave("Data/EnemyWave.json");

    if (!file_enemyWave.is_open()) {

        DxPlus::Utils::FatalError(L"wave読み込めなかったjson");
        return;
    }
    

    json waveData;
    file_enemyWave >> waveData;

    enemyWaves.clear();
    enemyWaves.reserve(256);

    for (const auto& waveJson : waveData["waves"]) {
        auto wave = std::make_shared<EnemyWave>();

        wave->key        = waveJson["key"];
        wave->spawnCount = waveJson["spawnCount"];
        wave->spawnDelay = waveJson["spawnDelay"];

        enemyWaves.push_back(wave);

        int a = 0;
    }
    int aa = 2;
}

std::shared_ptr<EnemyStatus> EnemyDataMaster::GetEnemyStatus(EnemyKey key)
{
    return enemyAllData[key];
}

std::shared_ptr<EnemyWave> EnemyDataMaster::GetEnemyWave(size_t idx)
{

    int a =1;
    if (idx >= enemyWaves.size()) {

        DxPlus::Utils::FatalError(L"Game Over Thank You");
    }

    return enemyWaves[idx];
}
