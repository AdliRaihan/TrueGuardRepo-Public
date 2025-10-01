#include "NPCInventoryCases.h"
#include <spdlog/spdlog.h>

using namespace RE;

BSEventNotifyControl InventorySink::ProcessEvent(
    const TESContainerChangedEvent* event,
    BSTEventSource<TESContainerChangedEvent>*)
{
    if (!event)
        return BSEventNotifyControl::kContinue;

    auto* oldCont = TESForm::LookupByID<TESObjectREFR>(event->oldContainer);
    auto* newCont = TESForm::LookupByID<TESObjectREFR>(event->newContainer);
    auto* pc = RE::PlayerCharacter::GetSingleton();

    if (newCont == pc)
        DebugNotification("Item Added");
    if (oldCont == pc)
        DebugNotification("Item Lost");
    
    return BSEventNotifyControl::kContinue;
}

// single definition of sink
static InventorySink g_containerChangedSink;

void RegisterInventoryEvents()
{
    if (auto* src = ScriptEventSourceHolder::GetSingleton())
        src->AddEventSink(&g_containerChangedSink);
}