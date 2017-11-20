#include "TB3D_Configuration.h"

TB3D_Configuration* TB3D_Configuration::M_INSTANCE;
TB3D_Configuration* TB3D_Configuration::GetInstance() {
	if (TB3D_Configuration::M_INSTANCE == nullptr) {
		TB3D_Configuration::M_INSTANCE = new TB3D_Configuration();
	}
	return TB3D_Configuration::M_INSTANCE;
}