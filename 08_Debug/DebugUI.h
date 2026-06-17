// =============================
// DebugUI/DebugUI.h
// =============================
#pragma once
#include "../01_Core/GameContext.h"

class DebugUI
{
public:
    static DebugUI& GetInstance()
    {
        static DebugUI instance;
        return instance;
    }

    void Init();
    void Shutdown();

    void BeginFrame();
    void Draw(GameContext& ctx);
    void EndFrame();

private:
};
inline DebugUI& Debug() { return DebugUI::GetInstance(); }
