#include "TGLUIHooksDx11.h"

IDXGISwapChain* swapChainHook;
ID3D11Device* deviceHook;
ID3D11DeviceContext* contextHook;

static void* TGLUIHook_GetPresentAddr()
{
    DXGI_SWAP_CHAIN_DESC scd{};
    // Setting Up DXSwap Chain
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = GetForegroundWindow();
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    if (FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION, &scd,
        &swapChainHook, &deviceHook, nullptr, &contextHook)))
    {
        return nullptr;
    }

    // Finding Present index [8]
    void** vtable = *reinterpret_cast<void***>(swapChainHook);
    void* presentAddr = vtable[8];

    // DR
    swapChainHook->Release();
    deviceHook->Release();
    contextHook->Release();
    // E-DR

    return presentAddr;
}

bool TGLUIHook_Initialization()
{
    void* addr = TGLUIHook_GetPresentAddr();

    if (!addr) return false;

    if (MH_Initialize() != MH_OK) 
        return false;

    if (MH_CreateHook(addr, &hkPresent, reinterpret_cast<void**>(&oPresent)) != MH_OK) 
        return false;

    if (MH_EnableHook(addr) != MH_OK) 
        return false;

    return true;
}