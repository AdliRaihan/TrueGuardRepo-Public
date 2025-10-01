
#pragma once
#include <iostream>
#include <imgui.h>
#include <imgui_impl_win32.h>

struct UIInterfaceInjection {
public:
    ImFont* _regularFont;
    ImFont* _boldFont;
	virtual void draw() = 0;
    float getWidth(int div = 1);
    float getHeight(int div = 1);

    void pushFont(ImFont* __regularFont, ImFont* __boldFont) {
        _regularFont = __regularFont;
        _boldFont = __boldFont;
    }

    void makeShadowedText(
        ImDrawList* drawList, 
        ImVec2 pos,
        std::string text,
        ImU32 color,
        ImFont* font = nullptr
    ) {
        float x = 0;

        if (font) {
            x = font->CalcTextSizeA(font->LegacySize, FLT_MAX, 0.0f, text.c_str()).x;
        }

        pos.x -= x;

        drawList->AddText(
            ImVec2(pos.x - 1, pos.y + 1),
            IM_COL32(0, 0, 0, 255),
            text.c_str()
        );
        drawList->AddText(
            pos,
            color,
            text.c_str()
        );
    }
};