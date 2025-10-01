
#pragma once
#include "TrueGuardLib.h"

// My Mod
#include "Sources/NPCInventoryCases.h"
#include "Sources/InputEventListener.h"

// Delete this later

// Just For Debug Entry Point
#include <Windows.h>
#include <spdlog/sinks/basic_file_sink.h>

void InitializeLogging() {
    auto path = logger::log_directory();
    if (!path) return;

    *path /= "TrueGuard.log";  
    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
    auto log = std::make_shared<spdlog::logger>("global log", std::move(sink));
    spdlog::set_default_logger(log);
    spdlog::set_pattern("%H:%M:%S [%^%l%$] %v");
    spdlog::set_level(spdlog::level::debug);
}

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
    InitializeLogging();
    // --> Just for debug i'm too lazy writing log file
    // TODO: Make Log file instead of window
    // ::MessageBoxA(nullptr, "WARNING: True Guard Pagman Loaded V0.1! ", "SKESPLUGINDEBUGWAW!", MB_OK | MB_ICONWARNING);
    
    // --> If Running should return handle != 0 in the logs
    SKSE::Init(skse);

    auto pap = SKSE::GetPapyrusInterface();

    TestUIImpl::registerMenu();

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
        switch (msg->type) {
        case SKSE::MessagingInterface::kDataLoaded:
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
