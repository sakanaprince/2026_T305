#include "EnemyDataMaster.h"


#include <fstream>
#include "../DxPlus/DxPlus.h"

void EnemyDataMaster::LoadJson()
{
    using json = nlohmann::json;

    std::ifstream file("Data/EnemyData.json");

    if (!file.is_open()) {

        DxPlus::Utils::FatalError(L"読み込めなかったjson");
        return;
    }

    // 2. ファイルの中身を丸ごとJSONオブジェクトにパース（解析）する
    json data;
    file >> data;

    // 3. JSONの配列（"enemies"）をループで回して、構造体に割り当てていく
    for (const auto& enemyJson : data["enemies"]) {
        auto enemy = std::make_shared<EnemyStatus>();

        // json["キー名"] で型を自動判別して代入してくれる（超便利！）
        enemy->key = enemyJson["key"];
        enemy->maxHp = enemyJson["maxHp"];


        // データベース（Map）に登録
        enemyAllData[enemy->key] = enemy;
    }
}

std::shared_ptr<EnemyStatus> EnemyDataMaster::GetEnemyStatus(EnemyKey key)
{
    return enemyAllData[key];
}
