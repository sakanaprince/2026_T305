#include "DxLib.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

bool g_raise_imgui_viewports = false;

//3dpg1参照...
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
);



static LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //F12キーで飛べるのに「定義されてない」とは
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



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ウィンドウモードにする（これがないと全画面になります）
    ChangeWindowMode(false);
    SetGraphMode(1920, 1080, 32);
    SetHookWinProc(CustomWinProc); // これが必要！


    //画面拡大率に関わらず表示するために(ImGUIのズレを拡大率に依存させない)
    SetWindowSizeExtendRate(1.0f);


    // DXライブラリの初期化に失敗したらおしまい
    if (DxLib_Init() == -1) { return -1; }

    if (SetMouseDispFlag(TRUE) == -1) { MessageBox(NULL, L"なんかマウスえらった", L"正常に終わった", MB_OK); }
    SetWindowText(L"DESTROYER");

    // --- ここにゲームの処理を書いていく ---
    bool isDebugMode = false;
    int lastTime = GetNowCount();
    int screenWidth, screenHeight;
    GetDrawScreenSize(&screenWidth, &screenHeight);
    SetWaitVSyncFlag(TRUE);

    //=============ImGUI初期設定（3dpg1のコードを参照）=============
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(GetMainWindowHandle());
    auto* device = reinterpret_cast<ID3D11Device*>(const_cast<void*>(DxLib::GetUseDirect3D11Device()));
    auto* context = reinterpret_cast<ID3D11DeviceContext*>(const_cast<void*>(DxLib::GetUseDirect3D11DeviceContext()));
    ImGui_ImplDX11_Init(device, context);
    //フォント設定
    ImGuiIO& io = ImGui::GetIO();
    //=============ImGUI初期設定（3dpg1のコードを参照）==============


    // 日本語フォント（MSゴシックなど）を読み込む
    // GetGlyphRangesJapanese() を渡すのがポイントです
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msgothic.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    //ダブルバッファリング（画面のちらつきを止めるために２つのスクリーンを使うやつ)
    SetDrawScreen(DX_SCREEN_BACK);

    // ------------------------------------

    return 0;
}