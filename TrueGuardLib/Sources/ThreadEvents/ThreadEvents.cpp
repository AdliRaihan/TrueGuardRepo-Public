
#include "ThreadEvents.h"
#include "../UIs/DutyGuardUI.h"
#include "../UIHooks/TGLUIHooksDx11.h"

DutyGuardUI* guardUI = nullptr;

RE::MenuTopicManager* targetDialogue = RE::MenuTopicManager::GetSingleton();

static std::atomic<bool> g_RunTimer{ true };

static std::atomic<int>  g_GuardSecondsLeft{ 0 };

void ThreadEvents::DialogueEvent(int seconds) {
    g_GuardSecondsLeft = seconds;

	std::thread([] {
        while (g_RunTimer) {

            std::this_thread::sleep_for(std::chrono::seconds(1));

            auto* targetDialogue = RE::MenuTopicManager::GetSingleton();

            if (!targetDialogue) {
                TGL::Hooks::destroyCurrentInjectedUIs(guardUI);
                continue;
            }

            RE::ObjectRefHandle currentDialogueActor = targetDialogue->speaker;

            if (!currentDialogueActor) {
                TGL::Hooks::destroyCurrentInjectedUIs(guardUI);
                continue;
            }

            RE::Actor* actorDialogue = currentDialogueActor.get()->As<RE::Actor>();

            if (!actorDialogue) {
                TGL::Hooks::destroyCurrentInjectedUIs(guardUI);
                continue;
            }

            RE::TESNPC* playerBase = RE::PlayerCharacter::GetSingleton()->GetActorBase();
            RE::TESNPC* npcBase = actorDialogue->GetActorBase();

            if (!playerBase || !npcBase) {
                TGL::Hooks::destroyCurrentInjectedUIs(guardUI);
                continue;
            }

            RE::BGSRelationship* relship = RE::BGSRelationship::GetRelationship(
                RE::PlayerCharacter::GetSingleton()->GetActorBase(), actorDialogue->GetActorBase()
            );

            int level = -99;

            if (relship)
                level = relship->level.underlying();

            if (guardUI == nullptr)
                guardUI = new DutyGuardUI();

            guardUI->nameDisplay = actorDialogue->GetDisplayFullName();
            guardUI->relationshipRank = level;

            TGL::Hooks::InjectUI(guardUI);
        }
    }).detach();
}