#pragma once
#include "../DxPlus/DxPlus.h"

class GameContext
{
public:
    GameContext() = default;
    ~GameContext() = default;

    void Init();
    void Reset();
    void Update(float deltaTime);
    void Draw() const;

private:
};
