
#include <iostream>

// Actually this is global shared instance not constant
// UNUSED
class GlobalConstant {
public:
	static int overlayMenu;
	static std::string misc_CurrentActiveNPC;
	static void toggleOverlayMenu();
	static void setCurrentActiveNPC(std::string _val);
};