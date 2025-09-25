#include "NPCInventoryCases.h"
#include <spdlog/spdlog.h>

RE::BSEventNotifyControl InventorySink::ProcessEvent(
    const RE::TESContainerChangedEvent* event,
    RE::BSTEventSource<RE::TESContainerChangedEvent>*)
{
    if (!event)
        return RE::BSEventNotifyControl::kContinue;

    auto* oldCont = RE::TESForm::LookupByID<RE::TESObjectREFR>(event->oldContainer);
    auto* newCont = RE::TESForm::LookupByID<RE::TESObjectREFR>(event->newContainer);
    auto* pc = RE::PlayerCharacter::GetSingleton();

    if (newCont == pc)
        RE::DebugNotification("Item Added");
    if (oldCont == pc)
        RE::DebugNotification("Item Lost");

    return RE::BSEventNotifyControl::kContinue;
}

// single definition of sink
static InventorySink g_containerChangedSink;

void RegisterInventoryEvents()
{
    if (auto* src = RE::ScriptEventSourceHolder::GetSingleton())
        src->AddEventSink(&g_containerChangedSink);
}