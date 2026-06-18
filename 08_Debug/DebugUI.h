#pragma once
#include "../01_Core/GameContext.h"
#include <unordered_map>

struct  DebugLog
{
    std::string variableText = "";
    int cnt = 1;
};

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


    void Log(const std::string& text, const bool& variable);
    void Log(const std::string& text, const float& variable);
    void Log(const std::string& text, const int& variable);
    void Log(const std::string& text, const Vec3& variable);
    void Log(const std::string& text);

private:
    std::unordered_map<std::string, DebugLog> debugText;
    void LogSetting(const std::string& text, const std::string variableText);
};
inline DebugUI& Debug() { return DebugUI::GetInstance(); }
