#include "TAKEnhancedDll/Wrappers/BuildMenuWrapper.h"
#include "TAKEnhancedDll/GlobalState.hpp"

BuildMenuWrapper::BuildMenuWrapper(std::shared_ptr<BuildMenu*> buildMenu, uintptr_t baseAddress)
{
    this->baseAddress = baseAddress;
    _buildMenu = std::make_shared<BuildMenu*>(*buildMenu);
}

void BuildMenuWrapper::initializeButtonsWrappers()
{
    logger->debug("Loading Build Menu...");
    logger->debug("First button ptr: %x", (*_buildMenu)->children);
    logger->debug("Last button ptr: %x", (*_buildMenu)->last);

    uintptr_t* children = (*_buildMenu)->children;
    uintptr_t* last = (*_buildMenu)->last;

    if (children == nullptr || last == nullptr) {
        return;
    }
    
    BuildButton** next_build_button = (BuildButton**) children;
    BuildButton** last_build_button = (BuildButton**) last;

    while (next_build_button != last_build_button) {
        logger->debug("Loading button at address: %x", *next_build_button);
        this->buttons.push_back(BuildButtonWrapper(*next_build_button, this->baseAddress));
        next_build_button++;
    }

    logger->debug("Build Menu loaded successfully.");

    for (int i = 0; i < this->buttons.size(); i++) {
        auto button = this->buttons.at(i);
        logger->debug("Button %d: %x", i, *button._buildButton);
    }
}

void BuildMenuWrapper::reinitializeButtonsWrappers()
{
    this->buttons.clear();
    initializeButtonsWrappers();
}
