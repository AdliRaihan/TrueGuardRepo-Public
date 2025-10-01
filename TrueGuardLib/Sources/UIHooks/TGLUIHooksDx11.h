#include <RE/Skyrim.h>
#include <MinHook.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <tchar.h>
#include "../DependencyInjection/UIInterfaceInjection.h"

// Methods
namespace TGL::Hooks {
	bool TGLUIHook_Initialization();
	void InjectUI(UIInterfaceInjection* instance);
	void destroyCurrentInjectedUIs();
}