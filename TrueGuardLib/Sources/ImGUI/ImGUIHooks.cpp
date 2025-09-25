#include "ImGUIHooks.h"

// Device
ID3D11Device* device;
// Current Context
ID3D11DeviceContext* context;
// Render Target View
ID3D11RenderTargetView* mainRTV;

HRESULT(__stdcall* oPresent)(IDXGISwapChain* swap, UINT sync, UINT flags);

// ResizeBuffers_t oResizeBuffers;
static WNDPROC g_OrigWndProc = nullptr;
static bool g_UiOpen = true; // toggle however you like

LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    return CallWindowProc(g_OrigWndProc, hWnd, msg, wParam, lParam);
}

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
        ImGui::StyleColorsDark();

        init = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello Skyrim + (MinHook & IMGUI)!", nullptr, ImGuiWindowFlags_None);
    ImGui::Text("Testing functionality Bruh!");

    ImGuiIO& _ioPtr = ImGui::GetIO();
    _ioPtr.WantCaptureMouse = false;
    _ioPtr.MouseDrawCursor = true;

    ImGui::End();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(swap, sync, flags);
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