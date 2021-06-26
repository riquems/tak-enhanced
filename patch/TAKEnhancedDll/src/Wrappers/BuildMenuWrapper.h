#pragma once

#include "Models/UI/BuildMenu.h"

#include "BuildButtonWrapper.h"
#include <iostream>

class BuildMenuWrapper
{
public:
	std::shared_ptr<BuildMenu*> _buildMenu;

	std::vector<BuildButtonWrapper> buttons;

	BuildMenuWrapper(std::shared_ptr<BuildMenu*> buildMenu)
	{
		_buildMenu = std::make_shared<BuildMenu*>(*buildMenu);
	}

	void initializeButtonsWrappers();
	void reinitializeButtonsWrappers();
	bool isOpen();
};

void BuildMenuWrapper::initializeButtonsWrappers()
{
	uintptr_t* children = (*_buildMenu.get())->children;
	uintptr_t* last = (*_buildMenu.get())->last;

	if (children == nullptr || last == nullptr) {
		return;
	}
	
	BuildButton** next_build_button = (BuildButton**) children;
	BuildButton** last_build_button = (BuildButton**) last;

	while (*next_build_button != *last_build_button) {
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
	return (*_buildMenu.get())->visible;
}