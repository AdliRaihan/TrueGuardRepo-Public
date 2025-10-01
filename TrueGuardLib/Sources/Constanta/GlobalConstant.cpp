
#include "GlobalConstant.h"
#include <RE/Skyrim.h>

using namespace std;
// UNUSED
// TODO: CLEAN THIS MESS :(
string GlobalConstant::misc_CurrentActiveNPC = "";

int GlobalConstant::overlayMenu = 0;

void GlobalConstant::toggleOverlayMenu() {
	if (overlayMenu == 0) {
		overlayMenu = 1;
		return;
	}
	overlayMenu = 0;
}

void GlobalConstant::setCurrentActiveNPC(string _val) {
	misc_CurrentActiveNPC = _val;
}

float GlobalConstant::getWidth(int div) {
	auto* state = RE::BSGraphics::Renderer::GetSingleton();
	return state->GetScreenSize().width / div;
}

float GlobalConstant::getHeight(int div) {
	auto* state = RE::BSGraphics::Renderer::GetSingleton();
	return state->GetScreenSize().height / div;
}