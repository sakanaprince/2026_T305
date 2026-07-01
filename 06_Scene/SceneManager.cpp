#include "SceneManager.h"
#include "../04_Resource/ResourceManager.h"
#include "../DxPlus/DxPlus.h"

#include "../08_Debug/DebugUI.h"

void SceneManager::Init()
{
    const int w = DxPlus::CLIENT_WIDTH;
    const int h = DxPlus::CLIENT_HEIGHT;

    DxPlus::Initialize(w, h, runConfig.windowed);


#ifndef NDEBUG
    // Debug のときだけ、さらに windowed のときだけ DebugUI を許可
    if (runConfig.enableDebugUI && runConfig.windowed)
    {
        Debug().Init();
    }
#endif
    DxPlus::DxWrapper::GetInstance().SetFpsCap(runConfig.fpsCap);

    ResourceManager::GetInstance().LoadAll();
    gameContext.Init();

    titleScene.SetGameContext(&gameContext);
    gameScene.SetGameContext(&gameContext);
    gameOverScene.SetGameContext(&gameContext);
    gameClearScene.SetGameContext(&gameContext);

    scene = &titleScene; // 最初のシーン
}

void SceneManager::Shutdown()
{
    ResourceManager::GetInstance().UnloadAll();

#ifndef NDEBUG
    if (runConfig.enableDebugUI && runConfig.windowed)
    {
        Debug().Shutdown();
    }
#endif

    DxPlus::Shutdown();
}

void SceneManager::SetScene(Scene* newScene)
{
    if (!newScene || newScene == scene) return;
    scene = newScene; // 破棄しない＝常駐
}

Scene* SceneManager::GetScene(SceneID id)
{
    switch (id)
    {
        case SceneID::Title:      return &titleScene;
        case SceneID::Game:       return &gameScene;
        case SceneID::GameOver:   return &gameOverScene;
        case SceneID::GameClear:  return &gameClearScene;
    }
    return &titleScene;
}

void SceneManager::Run()
{
    //現在シーンのInit()を呼ぶ
    if (scene) scene->Init();

    //ゲーム中の処理
    //DxPlusだとFPSの設定ができる。if (DxLib::ProcessMessage() != 0)これでも動く。
    while (DxPlus::GameLoop(true))
    {

        //入力を受け取るための処理
        DxPlus::Input::Update();

        if (scene)
        {
            DxLib::ClearDrawScreen();

            float deltaTime = DxPlus::GetDeltaTime();
            scene->Drive(deltaTime);
            scene->Render();

            //フェードが終了しているかどうか
            if (scene->IsFinished())
            {
                //現在シーンのEnd()を呼ぶ
                scene->End();

                //次のシーンの設定
                Scene* next = scene->GetNextScene();
                //今のシーンで設定していたNextSceneをnullにする
                scene->SetNextScene(nullptr);

                //次のシーンが存在してたら現在のシーンを次のシーンにする
                if (!next) { DxLib::ScreenFlip(); break; }
                SetScene(next);
                //Init()を呼ぶ(SetScene()でsceneにnextを入れてるからsceneでも可)
                next->Init();
            }

            DxPlus::Debug::Draw();
            scene->DrawFadeOverlay();

#ifndef NDEBUG
            //DebugUI
            if (runConfig.enableDebugUI && runConfig.windowed)
            {
                Debug().BeginFrame();
                Debug().Draw(gameContext);
                Debug().EndFrame();
            }
#endif

            DxLib::ScreenFlip();
        }
    }
}
