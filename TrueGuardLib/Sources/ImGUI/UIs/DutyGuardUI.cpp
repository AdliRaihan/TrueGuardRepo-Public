#include "DutyGuardUI.h"

using namespace ImGui;

void DutyGuardUI::draw() {
    ImDrawList* dl = ImGui::GetForegroundDrawList();

    static ImVec2 pos(0, 0), size(360, 46);

    ImVec2 p0 = pos, p1 = ImVec2(
        pos.x + size.x,
        pos.y + size.y
    );

    PushFont(DutyGuardUI::_regularFont);
    const char* dutyHeader = "True Guard Status";
    dl->AddText(
        ImVec2(p0.x + 11, p0.y + 13),
        IM_COL32(0, 0, 0, 255),
        dutyHeader
    );
    dl->AddText(
        ImVec2(p0.x + 12, p0.y + 12),
        IM_COL32(255, 255, 255, 255),
        dutyHeader
    );
    PopFont();

    PushFont(DutyGuardUI::_boldFont);
    const char* offDutyWord = "Off Duty Guard";
    dl->AddText(
        ImVec2(p0.x + 11, p0.y + 37),
        IM_COL32(0, 0, 0, 255),
        offDutyWord
    );
    dl->AddText(
        ImVec2(p0.x + 12, p0.y + 36),
        IM_COL32(255, 255, 255, 255),
        offDutyWord
    );

    const char* DisplayName = DutyGuardUI::nameDisplay.c_str();
    dl->AddText(
        ImVec2(p0.x + 11, p0.y + 63),
        IM_COL32(0, 0, 0, 255),
        DisplayName
    );
    dl->AddText(
        ImVec2(p0.x + 12, p0.y + 64),
        IM_COL32(255, 255, 255, 255),
        DisplayName
    );
    PopFont();
}