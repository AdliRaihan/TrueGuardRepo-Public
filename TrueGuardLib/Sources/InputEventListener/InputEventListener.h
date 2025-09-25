
#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

class InputSinkEvent :
	public RE::BSTEventSink<RE::InputEvent*> {
public:
	virtual RE::BSEventNotifyControl ProcessEvent(
		RE::InputEvent* const * iEvent,
		RE::BSTEventSource <RE::InputEvent*>*
	) override;
};

void RegisterInputListener();