#include "ImGUIHooks.h"
#include <corecrt_math.h>

#include <format>
#include <string>
#include <iostream>

// Device
ID3D11Device* device;
// Current Context
ID3D11DeviceContext* context;
// Render Target View
ID3D11RenderTargetView* mainRTV;

HRESULT(__stdcall* oPresent)(IDXGISwapChain* swap, UINT sync, UINT flags);

UIInterfaceInjection* injectedDrawing = nullptr;

ImFont* boldFont;
ImFont* regularFont;

// Toggle it 
bool g_menuOpen = false; 

HRESULT __stdcall hkPresent(IDXGISwapChain* swap, UINT sync, UINT flags) {
    static bool init = false;
    if (!init) {
        // init ImGui the first time
        swap->GetDevice(__uuidof(ID3D11Device), (void**)&device);
        device->GetImmediateContext(&context);

        DXGI_SWAP_CHAIN_DESC desc;
        swap->GetDesc(&desc);
        HWND hwnd = desc.OutputWindow;

        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(device, context);

        ImGuiIO& _ioPtr = ImGui::GetIO();

        _ioPtr.Fonts->AddFontDefault();

        boldFont = _ioPtr.Fonts->AddFontFromFileTTF(
            "Data/SKSE/Plugins/TrueGuardAssets/fonts/Quicksand-Bold.ttf", 16
        );

        regularFont = _ioPtr.Fonts->AddFontFromFileTTF(
            "Data/SKSE/Plugins/TrueGuardAssets/fonts/Quicksand-Regular.ttf", 16
        );

        ImGui_ImplDX11_CreateDeviceObjects();

        ImGui::StyleColorsDark();

        init = true;
    }

    if (!g_menuOpen)
        return oPresent(swap, sync, flags);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (injectedDrawing != nullptr)
        injectedDrawing->draw();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(swap, sync, flags);
}

void injectUI(UIInterfaceInjection* uiInjection) {
    uiInjection->pushFont(regularFont, boldFont);
    injectedDrawing = uiInjection;
}


static void CreateRenderTarget(IDXGISwapChain* swap) {
    ID3D11Texture2D* backBuffer = nullptr;
    if (SUCCEEDED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer))) {
        device->CreateRenderTargetView(backBuffer, nullptr, &mainRTV);
        backBuffer->Release();
    }
}

static void ReleaseRenderTarget() {
    if (mainRTV) { mainRTV->Release(); mainRTV = nullptr; }
}

void toggleMenu() {
    g_menuOpen = !g_menuOpen;
}