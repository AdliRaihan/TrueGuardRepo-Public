
#pragma once
#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

class TestUIImpl : 
    public RE::IMenu
{
public:
	static inline std::string MENU_NAME = "TEST_UI_IMPL";

    TestUIImpl()
    {
        using MF = RE::IMenu::Flag;
        menuFlags.set(MF::kUsesCursor);
        menuFlags.set(MF::kAlwaysOpen);
        // menuFlags.set(MF::kPausesGame); 

        depthPriority = 3;

        auto* scaleform = RE::BSScaleformManager::GetSingleton();
        if (scaleform) {
            scaleform->LoadMovie(
                this, 
                uiMovie, 
                "TrueGuard2",
                RE::BSScaleformManager::ScaleModeType::kShowAll, 
                1.0f);
        }
    }

	static RE::IMenu* make() {
		return new TestUIImpl();
	}

    static void registerMenu() {
        if (auto* ui = RE::UI::GetSingleton()) {
            ui->Register(MENU_NAME, &make);
        }
    }

    static void Open() {
        if (auto* q = RE::UIMessageQueue::GetSingleton())
            q->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
    }

    static void Close() {
        if (auto* q = RE::UIMessageQueue::GetSingleton())
            q->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
    }

    static bool IsOpen() {
        if (auto* ui = RE::UI::GetSingleton())
            return ui->IsMenuOpen(MENU_NAME);
        return false;
    }
};