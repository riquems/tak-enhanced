#pragma once

#include <iostream>
#include "Models/UI/BuildMenu.h"
#include "WindowManager.h"
#include "Models/UI/GameInterfaceHandler.h"
#include "ModelsExtensions/WindowExtensions.h"
#include "GameInterface.h"

class GameInterfaceManager
{
	WindowManager* window_manager;

public:
	GameInterfaceManager() {}

	std::shared_ptr<BuildMenu*> getBuildMenu();
};

std::shared_ptr<BuildMenu*> GameInterfaceManager::getBuildMenu()
{
	Window* InGameDesktop = GameInterface::GetWindow("InGameDesktop", baseAddress);

	if (InGameDesktop == nullptr)
		return nullptr;

	std::shared_ptr<Gadget*> gadget = window_manager->getGadget(InGameDesktop, "BuildMenu");

	std::shared_ptr<BuildMenu*> build_menu = std::reinterpret_pointer_cast<BuildMenu*>(gadget);

	return build_menu;
}