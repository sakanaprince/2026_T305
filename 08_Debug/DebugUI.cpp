#include "DebugUI.h"

#include <d3d11.h>
#include "DxLib.h"
#include "../01_Core/GameContext.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"

#include <filesystem>

extern bool g_raise_imgui_viewports;

void DebugUI::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // ===== 日本語フォント追加 =====
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = "./Data/Config/imgui.ini";
    //io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // ←これがDocking ON
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontFromFileTTF(
        "./Data/Fonts/Noto_Sans_JP/static/NotoSansJP-Regular.ttf", // ここは置いたパスに合わせる
        18.0f,
        nullptr,
        io.Fonts->GetGlyphRangesJapanese()
    );
    // ===========================

    ImGui_ImplWin32_Init(GetMainWindowHandle());
    auto* device = reinterpret_cast<ID3D11Device*>(const_cast<void*>(DxLib::GetUseDirect3D11Device()));
    auto* context = reinterpret_cast<ID3D11DeviceContext*>(const_cast<void*>(DxLib::GetUseDirect3D11DeviceContext()));
    ImGui_ImplDX11_Init(device, context);

    ImGui::LoadIniSettingsFromDisk("./Data/Config/imgui.ini");
}

void DebugUI::Shutdown()
{
    ImGui::SaveIniSettingsToDisk("./Data/Config/imgui.ini");
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void DebugUI::BeginFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGuiDockNodeFlags flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpaceOverViewport(ImGui::GetID("MainDockSpace"), ImGui::GetMainViewport(), flags);
}

void DebugUI::Draw(GameContext& ctx)
{
    if (ImGui::Begin("Log"))
    {
        if (ImGui::Button("Clear"))
        {
            debugText.clear();
        }

        for (auto& t : debugText)
        {
            ImGui::Text(u8"%s： %s： %d", t.first.c_str(), t.second.variableText.c_str(), t.second.cnt);
        }
    }

    ImGui::End();
}

void DebugUI::EndFrame()
{
    ImGuiIO& io = ImGui::GetIO();

    auto* context = reinterpret_cast<ID3D11DeviceContext*>(const_cast<void*>(DxLib::GetUseDirect3D11DeviceContext()));

    ID3D11RenderTargetView* oldRTV = nullptr;
    ID3D11DepthStencilView* oldDSV = nullptr;
    D3D11_VIEWPORT oldVP{};
    UINT vpCount = 1;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        context->OMGetRenderTargets(1, &oldRTV, &oldDSV);
        context->RSGetViewports(&vpCount, &oldVP);
    }

    // メインウィンドウのImGui描画
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // 外窓
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        // Viewport窓を前面へ（フォーカスは奪わない）
        if (g_raise_imgui_viewports)
        {
            ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
            for (int i = 0; i < pio.Viewports.Size; i++)
            {
                ImGuiViewport* vp = pio.Viewports[i];
                if (vp == ImGui::GetMainViewport()) continue;

                HWND hwnd = (HWND)vp->PlatformHandleRaw;
                if (!hwnd) continue;

                ::ShowWindow(hwnd, SW_SHOWNOACTIVATE);
                ::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
            }
            g_raise_imgui_viewports = false;
        }

        // 戻す（DxLibが期待するメインターゲットへ）
        context->OMSetRenderTargets(1, &oldRTV, oldDSV);
        context->RSSetViewports(1, &oldVP);

        if (oldRTV) oldRTV->Release();
        if (oldDSV) oldDSV->Release();
    }
}

void DebugUI::Log(const std::string& text, const bool& variable)
{
    switch (variable)
    {
    case 0:
        LogSetting(text, "FALSE");
        break;
    case 1:
        LogSetting(text, "TRUE");
        break;
    }
}

//小数点以下は6桁まで表示されます
void DebugUI::Log(const std::string& text, const float& variable)
{
    //std::stringstreamは必要最低限で表現するようになっているから、小数点以下の余分な0は消してくれるらしい
    std::stringstream ss;
    ss << variable;
    LogSetting(text, ss.str() + "f");
}

void DebugUI::Log(const std::string& text, const int& variable)
{
    LogSetting(text, std::to_string(variable).c_str());
}

void DebugUI::Log(const std::string& text)
{
    LogSetting(text, "");
}

void DebugUI::LogSetting(const std::string& text, const std::string variableText)
{
    if (auto t_it = debugText.find(text); t_it == debugText.end())
    {
        DebugLog log;
        log.variableText = variableText;
        debugText[text] = log;
    }
    else
    {
        if (t_it->second.variableText != variableText)
        {
            debugText[text].variableText = variableText;
            t_it->second.cnt = 0;
        }
        else
        {
            t_it->second.cnt++;
            t_it->second.cnt = std::min(t_it->second.cnt, 999);
        }
    }
}
