
#include "UIInterfaceInjection.h"
#include "../Constanta/GlobalConstant.h"

float UIInterfaceInjection::getHeight(int div) {
	return GlobalConstant::getHeight(div);
}

float UIInterfaceInjection::getWidth(int div) {
	return GlobalConstant::getWidth(div);
}