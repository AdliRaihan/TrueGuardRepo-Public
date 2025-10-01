#include "TGLUIHooksDx11.h"

// Typedefs
using PFN_D3D11CreateDeviceAndSwapChain =
HRESULT(WINAPI*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
    const D3D_FEATURE_LEVEL*, UINT, UINT,
    const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
    ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext*);

using Present_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
using ResizeBuffers_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

// Globals
static PFN_D3D11CreateDeviceAndSwapChain g_OriCreateDSC = nullptr;
static Present_t       g_OriPresent = nullptr;
static ResizeBuffers_t g_OriResizeBuffers = nullptr;
static IDXGISwapChain* g_SwapChain = nullptr;

int mult = 0;
int multMax = 50;

// Device
ID3D11Device* device;
// Current Context
ID3D11DeviceContext* context;
// Render Target View
ID3D11RenderTargetView* mainRTV;
// HWND
HWND hwnd;
// Active instance
UIInterfaceInjection* cInstance = nullptr;

ImFont* regularFont;
ImFont* boldFont;

static void CleanupRTV() {
    if (mainRTV) { mainRTV->Release(); mainRTV = nullptr; }
}

static void CreateRenderTarget(IDXGISwapChain* sc)
{
    CleanupRTV();
    ID3D11Texture2D* backBuffer = nullptr;
    if (SUCCEEDED(sc->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer)))
    {
        device->CreateRenderTargetView(backBuffer, nullptr, &mainRTV);
        backBuffer->Release();
    }
}

static HRESULT __stdcall Hook_Present(IDXGISwapChain* sc, UINT sync, UINT flags)
{
    static bool init = false;
    if (!init) {

        if (!device) {
            sc->GetDevice(__uuidof(ID3D11Device), (void**)&device);
        }

        if (device && !context) {
            device->GetImmediateContext(&context);
        }

        if (!hwnd) {
            DXGI_SWAP_CHAIN_DESC desc{};
            sc->GetDesc(&desc);
            hwnd = desc.OutputWindow;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(device, context);

        ImGuiIO& _ioPtr = ImGui::GetIO();

        _ioPtr.Fonts->AddFontDefault();

        boldFont = _ioPtr.Fonts->AddFontFromFileTTF(
            "Data/SKSE/Plugins/TrueGuardAssets/fonts/BarlowCondensed-Bold.ttf", 16
        );

        regularFont = _ioPtr.Fonts->AddFontFromFileTTF(
            "Data/SKSE/Plugins/TrueGuardAssets/fonts/BarlowCondensed-Medium.ttf", 16
        );

        CreateRenderTarget(sc);

        init = true;
    }

    if (!init || cInstance == nullptr)
        return g_OriPresent(sc, sync, flags);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    cInstance->draw();

    ImGui::Render();

    // Ensure RTV exists (after alt-tab)
    if (!mainRTV) CreateRenderTarget(sc);

    // Backup OM state, render, restore
    ID3D11RenderTargetView* prevRTV = nullptr;
    ID3D11DepthStencilView* prevDSV = nullptr;
    context->OMGetRenderTargets(1, &prevRTV, &prevDSV);

    context->OMSetRenderTargets(1, &mainRTV, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    context->OMSetRenderTargets(1, &prevRTV, prevDSV);
    if (prevRTV) prevRTV->Release();
    if (prevDSV) prevDSV->Release();

    return g_OriPresent(sc, sync, flags);
}

/*
    ========================================= DX Swap Chain Functions Goes below here....
*/

static HRESULT __stdcall Hook_ResizeBuffers(
    IDXGISwapChain* sc, UINT count, UINT w, UINT h, DXGI_FORMAT fmt, UINT opts)
{
    // Later...
    return g_OriResizeBuffers(sc, count, w, h, fmt, opts);
}

static void HookSwapchainVTableOnce(IDXGISwapChain* sc)
{
    if (g_OriPresent) return;

    void** vtbl = *reinterpret_cast<void***>(sc);
    void* presentAddr = vtbl[8];
    void* resizeAddr = vtbl[13];

    MH_CreateHook(presentAddr, &Hook_Present, reinterpret_cast<void**>(&g_OriPresent));
    MH_CreateHook(resizeAddr, &Hook_ResizeBuffers, reinterpret_cast<void**>(&g_OriResizeBuffers));
    MH_EnableHook(presentAddr);
    MH_EnableHook(resizeAddr);
}

static HRESULT WINAPI Hook_D3D11CreateDeviceAndSwapChain(
    IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    IDXGISwapChain** ppSwapChain,
    ID3D11Device** ppDevice,
    D3D_FEATURE_LEVEL* pFeatureLevel,
    ID3D11DeviceContext* ppImmediateContext)
{
    const HRESULT hr = g_OriCreateDSC(
        pAdapter, DriverType, Software, Flags,
        pFeatureLevels, FeatureLevels, SDKVersion,
        pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);

    if (SUCCEEDED(hr) && ppSwapChain && *ppSwapChain) {
        g_SwapChain = *ppSwapChain;
        HookSwapchainVTableOnce(g_SwapChain);
    }
    return hr;
}

void TGLUIHook_Shutdown()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    g_SwapChain = nullptr;
    g_OriPresent = nullptr;
    g_OriResizeBuffers = nullptr;
}

bool TGL::Hooks::TGLUIHook_Initialization()
{
    if (MH_Initialize() != MH_OK) return false;

    HMODULE hD3D11 = GetModuleHandleW(L"d3d11.dll");

    if (!hD3D11) return false;

    auto pCreate = reinterpret_cast<PFN_D3D11CreateDeviceAndSwapChain>(
        GetProcAddress(hD3D11, "D3D11CreateDeviceAndSwapChain"));

    if (!pCreate) return false;

    g_OriCreateDSC = pCreate;

    if (MH_CreateHook(reinterpret_cast<LPVOID>(pCreate),
        &Hook_D3D11CreateDeviceAndSwapChain,
        reinterpret_cast<void**>(&g_OriCreateDSC)) != MH_OK) return false;

    if (MH_EnableHook(reinterpret_cast<LPVOID>(pCreate)) != MH_OK) return false;

    return true;
}

void TGL::Hooks::InjectUI(UIInterfaceInjection* instance) {
    if (instance == cInstance)
        return;
    destroyCurrentInjectedUIs(instance);
    instance->pushFont(regularFont, boldFont);
    cInstance = instance;
}

void TGL::Hooks::destroyCurrentInjectedUIs(UIInterfaceInjection* instance) {
    if (!cInstance || instance == nullptr)
        return;
    if (cInstance == instance) { cInstance = nullptr; }
}