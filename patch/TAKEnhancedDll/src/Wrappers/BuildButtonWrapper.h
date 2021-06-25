#pragma once

#include "../Context.h"

#include "Functions/FunctionsOffsets.h"
#include "Models/UI/BuildButton.h"

class BuildButtonWrapper
{
public:
	BuildButton* _buildButton;
	BuildButtonWrapper(BuildButton* buildButton) : _buildButton(buildButton) {}

	void click();
};

void BuildButtonWrapper::click()
{
	uintptr_t buildButtonAddress = *(uintptr_t*) _buildButton;

	__asm {
		PUSH ECX
		MOV ECX, buildButtonAddress
	}

	void (*build_button_click)(int)  = (void (*)(int)) (FunctionsOffsets::buildButtonClick + baseAddress);

	build_button_click(1);

	__asm {
		POP ECX
	}
}