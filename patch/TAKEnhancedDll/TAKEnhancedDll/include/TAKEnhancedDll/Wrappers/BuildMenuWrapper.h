#pragma once

#include "TAKCore/Models/UI/BuildMenu.h"
#include "BuildButtonWrapper.h"

class BuildMenuWrapper
{
    uintptr_t baseAddress;
public:
    std::shared_ptr<BuildMenu*> _buildMenu;

    std::vector<BuildButtonWrapper> buttons;

    BuildMenuWrapper(std::shared_ptr<BuildMenu*> buildMenu, uintptr_t baseAddress);

    void initializeButtonsWrappers();
    void reinitializeButtonsWrappers();
};
