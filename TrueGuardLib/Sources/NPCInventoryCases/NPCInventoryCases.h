#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

class InventorySink :
    public RE::BSTEventSink<RE::TESContainerChangedEvent>
{
public:
    RE::BSEventNotifyControl ProcessEvent(
        const RE::TESContainerChangedEvent* event,
        RE::BSTEventSource<RE::TESContainerChangedEvent>*) override;
};

void RegisterInventoryEvents();