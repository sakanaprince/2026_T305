#pragma once
class Scene
{
public:
    virtual ~Scene() {} // デストラクタは必ずvirtualに

    // 読み込み、更新、描画、終了処理のセット
    virtual void Initialize() = 0; // 純粋仮想関数（継承先で必ず書く）
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() const = 0;
    virtual void End() = 0;
};

