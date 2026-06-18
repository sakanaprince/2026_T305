#include <crtdbg.h>
#include "../DxPlus/DxPlus.h"
#include "../06_Scene/SceneManager.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

bool g_raise_imgui_viewports = false;

static LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return 1; // ImGuiが処理した
	}

	if (msg == WM_ACTIVATEAPP && wParam == TRUE)
		g_raise_imgui_viewports = true;

	if (msg == WM_KEYDOWN && wParam == VK_ESCAPE)
	{
		PostQuitMessage(0);
		return 1;
	}

	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
    srand((unsigned int)time(NULL));
	DxLib::SetHookWinProc(CustomWinProc);
	SetWindowSizeExtendRate(1.0f);

    SceneManager::RunConfig cfg{};
#ifdef NDEBUG
    cfg.enableDebugUI = false;   // ReleaseはDebugUI完全禁止
#else
    cfg.enableDebugUI = true;
#endif

    // ウィンドウモード / フルスクリーンの切り替え
    cfg.windowed = true;

    SM().SetRunConfig(cfg);
	SM().Init();
	SM().Run();
	SM().Shutdown();

	return 0;
}
