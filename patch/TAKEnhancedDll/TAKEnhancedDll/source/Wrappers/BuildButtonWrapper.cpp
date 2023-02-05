#include "TAKEnhancedDll/Wrappers/BuildButtonWrapper.h"
#include "TAKCore/Functions/FunctionsOffsets.h"

BuildButtonWrapper::BuildButtonWrapper(BuildButton** buildButton, uintptr_t baseAddress)
{
    this->baseAddress = baseAddress;
    _buildButton = std::make_shared<BuildButton*>(*buildButton);
}

void BuildButtonWrapper::click()
{
    uintptr_t buildButtonAddress = *(uintptr_t*) (_buildButton.get());

    __asm {
        PUSH ECX
        MOV ECX, buildButtonAddress
    }

    void (__stdcall *build_button_click)(int)  = (void (__stdcall*)(int)) (FunctionsOffsets::buildButtonClick + this->baseAddress);

    build_button_click(1);

    __asm {
        POP ECX
    }
}