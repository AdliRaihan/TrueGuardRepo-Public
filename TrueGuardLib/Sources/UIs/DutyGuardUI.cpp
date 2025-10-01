#include "DutyGuardUI.h"
#include <RE/Skyrim.h>

using namespace ImGui;

struct RelLabel { const char* text; ImU32 color; };
static inline RelLabel RelToLabel(int r)
{
    /*
			kLover = 0,
			kAlly = 1,
			kConfidant = 2,
			kFriend = 3,
			kAcquaintance = 4,
			kRival = 5,
			kFoe = 6,
			kEnemy = 7,
			kArchnemesis = 8
    */
    switch (r) {
    case  0: return { "Lover",        IM_COL32(255, 170, 255, 255) };
    case  1: return { "Ally",         IM_COL32(120, 220, 120, 255) };
    case  2: return { "Confidant",    IM_COL32(120, 200, 255, 255) };
    case  3: return { "Friend",       IM_COL32(190, 220, 255, 255) };
    case  4: return { "Acquaintance", IM_COL32(220, 220, 220, 255) };
    case  5: return { "Rival",        IM_COL32(255, 210, 120, 255) };
    case  6: return { "Foe",          IM_COL32(255, 160, 120, 255) };
    case  7: return { "Enemy",        IM_COL32(255, 120, 120, 255) };
    case  8: return { "Archnemesis",  IM_COL32(255, 80,  80,  255) };
    default: return { "Unknown",      IM_COL32(200, 200, 200, 255) };
    }
}

void DutyGuardUI::draw() {

    ImDrawList* dl = ImGui::GetForegroundDrawList();

    float screenWidth = getWidth(2);

    float screenHeight = getHeight(2);

    ImVec2 posInfo(screenWidth - 5, 64);
    ImVec2 pos(screenWidth - 5, 74);

    RelLabel label = RelToLabel(relationshipRank);

    std::string dutyHeader = nameDisplay;
    std::string dutyStatus = label.text;

    _regularFont->LegacySize = 24;

    PushFont(DutyGuardUI::_regularFont);

    float textSizeHeight = _regularFont->CalcTextSizeA(24, FLT_MAX, 0.0f, dutyHeader.c_str()).y;

    ImU32 defaultTextColor = IM_COL32(220, 220, 220, 255);

    makeShadowedText(
        dl, 
        pos,
        dutyHeader, 
        defaultTextColor,
        _regularFont);

    makeShadowedText(
        dl,
        ImVec2(pos.x + 5, pos.y),
        dutyStatus,
        label.color);

    PopFont();

    _regularFont->LegacySize = 12;

    PushFont(DutyGuardUI::_regularFont);

    makeShadowedText(
        dl,
        posInfo,
        "NPC Name",
        defaultTextColor,
        _regularFont);

    makeShadowedText(
        dl,
        ImVec2(posInfo.x + 5, posInfo.y),
        "Relationship",
        label.color);
    PopFont();


 /*   ImVec2 p0 = pos, p1 = ImVec2(
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
    PopFont();*/
}