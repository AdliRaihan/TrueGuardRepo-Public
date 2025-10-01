
#pragma once
#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

class BaseMenu : 
	public RE::IMenu 
{
public:

	static inline std::string MENU_NAME;

	static RE::IMenu* make();

	static void registerMenu() {
		if (auto* ui = RE::UI::GetSingleton()) {
			ui->Register(MENU_NAME, &make);
		}
	}

    static void Open() {
        if (auto* q = RE::UIMessageQueue::GetSingleton())
            q->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr); }

    static void Close() {
        if (auto* q = RE::UIMessageQueue::GetSingleton())
            q->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr); }

    static bool IsOpen() {
        if (auto* ui = RE::UI::GetSingleton())
            return ui->IsMenuOpen(MENU_NAME);
        return false;
    }
};