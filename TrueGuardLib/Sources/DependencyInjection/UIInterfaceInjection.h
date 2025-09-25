
#pragma once
#include <iostream>

struct UIInterfaceInjection {
public:
    ImFont* _regularFont;
    ImFont* _boldFont;
	virtual void draw() = 0;

    void pushFont(ImFont* __regularFont, ImFont* __boldFont) {
        _regularFont = __regularFont;
        _boldFont = __boldFont;
    }
};