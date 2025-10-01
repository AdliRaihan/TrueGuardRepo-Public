#include <imgui.h>
#include <corecrt_math.h>
#include "../DependencyInjection/UIInterfaceInjection.h"

class DutyGuardUI : public UIInterfaceInjection {
public:
    std::string nameDisplay;
    int relationshipRank;
    void draw() override;
};