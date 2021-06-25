#pragma once

#include "Models/UI/BuildMenu.h"

class PlayerInterfaceManager
{
	GafManager* gaf_manager;

public:
	PlayerInterfaceManager() {}

	BuildMenu* getBuildMenu();
};

BuildMenu* PlayerInterfaceManager::getBuildMenu()
{
	Window* in_game_desktop = gaf_manager->getWindow("InGameDesktop");

	if (in_game_desktop == nullptr) {
		return nullptr;
	}

	BuildMenu* build_menu = (BuildMenu*) gaf_manager->getGadget(in_game_desktop, "BuildMenu");

	return build_menu;
}