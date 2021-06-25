#pragma once

#include "Models/UI/BuildMenu.h"

#include "BuildButtonWrapper.h"

class BuildMenuWrapper
{
public:
	BuildMenu* _buildMenu;

	std::vector<BuildButtonWrapper> buttons;

	BuildMenuWrapper(BuildMenu* buildMenu) : _buildMenu(buildMenu)
	{
		initializeButtonsWrappers();
	}

	void initializeButtonsWrappers();
	void reinitializeButtonsWrappers();
	bool isOpen();
};

void BuildMenuWrapper::initializeButtonsWrappers()
{
	BuildButton* next_build_button = (BuildButton*) _buildMenu->children;
	
	while (next_build_button != nullptr) {
		buttons.push_back(BuildButtonWrapper(next_build_button));
		next_build_button++;
	}
}

void BuildMenuWrapper::reinitializeButtonsWrappers()
{
	buttons.clear();
	initializeButtonsWrappers();
}


bool BuildMenuWrapper::isOpen()
{
	return _buildMenu->visible;
}