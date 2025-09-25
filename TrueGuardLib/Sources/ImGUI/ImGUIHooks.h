#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <tchar.h>
#include "../DependencyInjection/UIInterfaceInjection.h"

extern HRESULT(__stdcall* oPresent)(IDXGISwapChain* swap, UINT sync, UINT flags);
HRESULT __stdcall hkPresent(IDXGISwapChain* swap, UINT sync, UINT flags);
void injectUI(UIInterfaceInjection* uiInjection);
void toggleMenu();
