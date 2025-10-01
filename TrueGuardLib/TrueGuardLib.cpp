
#include "TrueGuardLib.h"

// My Mod
#include "Sources/NPCInventoryCases/NPCInventoryCases.h"
#include "Sources/InputEventListener/InputEventListener.h"
#include "Sources/UIHooks/TGLUIHooksDx11.h"
#include "Sources/ThreadEvents/ThreadEvents.h"

// Just For Debug Entry Point
#include <Windows.h>

// Entry Point SKSE - Skyrim 
SKSEPluginVersion = []() {
    SKSE::PluginVersionData v{};
    v.PluginName("TrueGuardLib");
    v.AuthorName("Dlyz");
    v.PluginVersion({ 1, 0, 0, 0 });
    // I dont think this part is necessary but for exstetique
    v.UsesUpdatedStructs();
    v.UsesAddressLibrary();
    v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST });
    return v;
    }();

SKSEPluginLoad(const SKSE::LoadInterface* skse) {

    // --> Just for debug i'm too lazy writing log file
    // TODO: Make Log file instead of window
    // ::MessageBoxA(nullptr, "WARNING: True Guard Pagman Loaded V0.1! ", "SKESPLUGINDEBUGWAW!", MB_OK | MB_ICONWARNING);
    
    // --> If Running should return handle != 0 in the logs
    SKSE::Init(skse);

    if (TGL::Hooks::TGLUIHook_Initialization()) {
        spdlog::info("UI Hooking successfully initiated!");
    }
    else {
        spdlog::info("UI Hooking Fails to initiates");
    }

    // MARK: TEMPORARY

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {

        auto TE = new ThreadEvents();

        switch (msg->type) {
        case SKSE::MessagingInterface::kDataLoaded:
            TE->DialogueEvent(1);
            break;
        case SKSE::MessagingInterface::kInputLoaded:
            break;
        case SKSE::MessagingInterface::kPostLoadGame:
            break;
        case SKSE::MessagingInterface::kPreLoadGame:
            break;
        default:
            break;
        }
    });
    
    return true;
}
