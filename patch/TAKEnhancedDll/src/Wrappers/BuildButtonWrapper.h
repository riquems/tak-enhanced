#pragma once

#include "../Context.h"

#include "Functions/FunctionsOffsets.h"
#include "Models/UI/BuildButton.h"

class BuildButtonWrapper
{
public:
    std::shared_ptr<BuildButton*> _buildButton;
    BuildButtonWrapper(BuildButton** buildButton)
    {
        _buildButton = std::make_shared<BuildButton*>(*buildButton);
    }

    void click();
};

void BuildButtonWrapper::click()
{
    uintptr_t buildButtonAddress = *(uintptr_t*) (_buildButton.get());

    __asm {
        PUSH ECX
        MOV ECX, buildButtonAddress
    }

    void (__stdcall *build_button_click)(int)  = (void (__stdcall*)(int)) (FunctionsOffsets::buildButtonClick + baseAddress);

    build_button_click(1);

    __asm {
        POP ECX
    }
}