#pragma once

#include <iostream>
#include "Models/UI/BuildMenu.h"

class PlayerInterfaceManager
{
	GafManager* gaf_manager;

public:
	PlayerInterfaceManager() {}

	std::shared_ptr<BuildMenu*> getBuildMenu();
};

std::shared_ptr<BuildMenu*> PlayerInterfaceManager::getBuildMenu()
{
	std::shared_ptr<Window*> in_game_desktop = gaf_manager->getWindow("InGameDesktop");

	if (in_game_desktop == nullptr) {
		return nullptr;
	}

	std::shared_ptr<Gadget*> gadget = gaf_manager->getGadget(in_game_desktop, "BuildMenu");

	std::shared_ptr<BuildMenu*> build_menu = std::reinterpret_pointer_cast<BuildMenu*>(gadget);

	return build_menu;
}