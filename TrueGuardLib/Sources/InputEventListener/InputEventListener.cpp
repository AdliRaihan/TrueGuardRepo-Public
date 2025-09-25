
#include "InputEventListener.h";
#include <Windows.h>

using namespace RE;

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
		auto dxScanCode = buttonEvent->GetIDCode();
		
		if (dxScanCode == RE::BSWin32KeyboardDevice::Key::kF1) {
			auto player = PlayerCharacter::GetSingleton();
			if (!player) return BSEventNotifyControl::kContinue;
			player->KillImpl(nullptr, 100, false, true);
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