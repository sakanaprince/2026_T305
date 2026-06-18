#pragma once
#include "Scene.h"
#include "../01_Core/GameContext.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "../08_Debug/DebugUI.h"
#include "../99_Utility/Const.h"

enum class SceneID { Title, Game, Result };

class SceneManager
{
public:
    static SceneManager& GetInstance()
    {
        static SceneManager instance;
        return instance;
    }

    void Init();
    void Shutdown();
    void Run();
    void SetScene(Scene* newScene);
    Scene* GetScene(SceneID id);

    GameContext& GetGameState() { return gameContext; }

    // コピー禁止
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    struct RunConfig
    {
        bool windowed = true;           // Releaseでも切替可
        bool enableDebugUI = true;      // Debug専用にしたいなら main で false にする
        int fpsCap = Const::FPS_CAP;
    };
    void SetRunConfig(const RunConfig& cfg) { runConfig = cfg; }

private:
    SceneManager() = default;
    ~SceneManager() = default;

    GameContext gameContext;
    TitleScene  titleScene{ &gameContext };
    GameScene   gameScene{ &gameContext };
    ResultScene resultScene{ &gameContext };

    Scene* scene = nullptr; // 現在のシーン

    RunConfig runConfig{};
    DebugUI debugUI;
};
inline SceneManager& SM() { return SceneManager::GetInstance(); } // ショートカット
