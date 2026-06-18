#include "SceneManager.h"
#include "../04_Resource/ResourceManager.h"
#include "../DxPlus/DxPlus.h"

#include "../08_Debug/DebugUI.h"

void SceneManager::Init()
{
    const int w = DxPlus::CLIENT_WIDTH;
    const int h = DxPlus::CLIENT_HEIGHT;

    DxPlus::Initialize(w, h, runConfig.windowed);
    DxLib::SetMouseDispFlag(TRUE);

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
    resultScene.SetGameContext(&gameContext);

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
        case SceneID::Title:    return &titleScene;
        case SceneID::Game:     return &gameScene;
        case SceneID::Result:   return &resultScene;
    }
    return &titleScene;
}

void SceneManager::Run()
{
    if (scene) scene->Init();
    while (DxPlus::GameLoop(true))
    {
        DxPlus::Input::Update();

        if (scene)
        {
            DxLib::ClearDrawScreen();

            //DxPlus::Debug::SetString(L"大阪情報コンピュータ専門学校（OIC）");
            //DxPlus::Debug::SetString(L"３ＤゲームプログラミングⅠ");
            //DxPlus::Debug::SetString(L"07_Sample");
            //DxPlus::Debug::SetString(L"");

            float deltaTime = DxPlus::GetDeltaTime();
            scene->Drive(deltaTime);
            scene->Render();

            if (scene->IsFinished())
            {
                scene->End();

                Scene* next = scene->GetNextScene();
                scene->SetNextScene(nullptr);

                if (!next) { DxLib::ScreenFlip(); break; }
                SetScene(next);
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
