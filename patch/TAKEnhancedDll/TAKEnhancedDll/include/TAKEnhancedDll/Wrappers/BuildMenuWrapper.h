#pragma once

#include "TAKCore/Models/UI/BuildMenu.h"
#include "BuildButtonWrapper.h"

class BuildMenuWrapper
{
    uintptr_t baseAddress;
public:
    BuildMenu* _buildMenu;

    std::vector<BuildButtonWrapper> buttons;

    BuildMenuWrapper(BuildMenu* buildMenu, uintptr_t baseAddress);

    void initializeButtonsWrappers();
    void reinitializeButtonsWrappers();
};
