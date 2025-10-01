
#include "InputEventListener.h";
#include "../Constanta/GlobalConstant.h"

// UIs
#include "../UIHooks/TGLUIHooksDx11.h"
#include "../UIs/DutyGuardUI.h"

using namespace RE;

DutyGuardUI* guardUI = nullptr;

BSEventNotifyControl InputSinkEvent::ProcessEvent(
	InputEvent* const* iEvent,
	BSTEventSource <InputEvent*>*
) {

	if (!iEvent)
		return BSEventNotifyControl::kContinue;

	InputEvent* _iEvent = *iEvent;
	
	if (!_iEvent)
		return BSEventNotifyControl::kContinue;

	if (_iEvent->eventType == RE::INPUT_EVENT_TYPE::kButton) {
		auto* buttonEvent = _iEvent->AsButtonEvent();

		// Ignore fast toggle because it makes the UI glitchy
		if (!buttonEvent->IsDown())
			return BSEventNotifyControl::kContinue;

		auto dxScanCode = buttonEvent->GetIDCode();

		switch (dxScanCode) {
		case RE::BSWin32KeyboardDevice::Key::kF1:
			break;
		case RE::BSWin32KeyboardDevice::Key::kG:
			getCurrentCrosshairTarget();
			break;
		default:
			break;
		}
	}

	return BSEventNotifyControl::kContinue;
}

static InputSinkEvent g_inputSinkEvent;

void RegisterInputListener() {
	if (auto uiLoad = RE::BSInputDeviceManager::GetSingleton()) {
		uiLoad->AddEventSink(&g_inputSinkEvent);
	}
}

void getCurrentCrosshairTarget() {
	// MOVE THIS LINE TO UTILS LATER
	CrosshairPickData* pickData = RE::CrosshairPickData::GetSingleton();
	
	if (!pickData)
		return;

	auto refs = pickData->target;

	if (!refs)
		return;

	auto objRefs = refs.get();

	if (!objRefs.get())
		return;
	// END OF THIS LINE TO UTILS LATER

	if (guardUI == nullptr)
		guardUI = new DutyGuardUI();

	guardUI->nameDisplay = objRefs.get()->GetDisplayFullName();

	TGL::Hooks::InjectUI(guardUI);
}