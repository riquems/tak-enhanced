#pragma once

#include "TAKCore/Models/UI/BuildButton.h"

class BuildButtonWrapper
{
    uintptr_t baseAddress;

public:
    std::shared_ptr<BuildButton*> _buildButton = nullptr;
    BuildButtonWrapper(BuildButton** buildButton, uintptr_t baseAddress);

    void click();
};
