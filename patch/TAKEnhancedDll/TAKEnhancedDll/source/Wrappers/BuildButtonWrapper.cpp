#include "TAKEnhancedDll/Wrappers/BuildButtonWrapper.h"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKCore/Functions/FunctionsOffsets.h"

BuildButtonWrapper::BuildButtonWrapper(BuildButton* buildButton, uintptr_t baseAddress)
{
    this->baseAddress = baseAddress;
    _buildButton = std::make_shared<BuildButton*>(buildButton);
}

void BuildButtonWrapper::click()
{
    uintptr_t* buildButton = (uintptr_t*) *_buildButton;

    logger->debug("Clicking button at %x", buildButton);

    __asm {
        PUSH ECX
        MOV ECX, buildButton
    }

    void (__stdcall *build_button_click)(int)  = (void (__stdcall*)(int)) (FunctionsOffsets::buildButtonClick + this->baseAddress);

    build_button_click(1);

    __asm {
        POP ECX
    }
}