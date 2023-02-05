#include "TAKEnhancedDll/Wrappers/BuildMenuWrapper.h"

BuildMenuWrapper::BuildMenuWrapper(std::shared_ptr<BuildMenu*> buildMenu, uintptr_t baseAddress)
{
    this->baseAddress = baseAddress;
    _buildMenu = std::make_shared<BuildMenu*>(*buildMenu);
}

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
        this->buttons.push_back(BuildButtonWrapper(next_build_button, this->baseAddress));
        next_build_button++;
    }
}

void BuildMenuWrapper::reinitializeButtonsWrappers()
{
    this->buttons.clear();
    initializeButtonsWrappers();
}
