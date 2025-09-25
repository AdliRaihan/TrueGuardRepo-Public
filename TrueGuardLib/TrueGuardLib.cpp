
#include "TrueGuardLib.h"

// Just For Debug Entry Point
#include <Windows.h>

// Entry Point SKSE - Skyrim 
SKSEPluginVersion = []() {
    SKSE::PluginVersionData v{};
    v.PluginName("SkyrimRelationshipSKSE");
    v.AuthorName("YourName");
    v.PluginVersion({ 1, 0, 0, 0 });
    v.UsesUpdatedStructs();
    v.UsesAddressLibrary();
    v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST });
    return v;
    }();

SKSEPluginLoad(const SKSE::LoadInterface* skse) {

    // --> Just for debug i'm too lazy writing log file
    // TODO: Make Log file instead of window
    ::MessageBoxA(nullptr, "WARNING: True Guard Pagman Loaded V0.1! ", "SKESPLUGINDEBUGWAW!", MB_OK | MB_ICONWARNING);
    
    // --> If Running should return handle != 0 in the logs
    SKSE::Init(skse);
    
    return true;
}
