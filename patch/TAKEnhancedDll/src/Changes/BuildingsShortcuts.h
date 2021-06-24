#pragma once
#include <BuildMenu.h>

void SelectBuilding(int pos)
{
	unsigned int InGameDesktopAddress;
	unsigned int BuildMenuAddress;
	unsigned int BuildButtonAddress;

	unsigned int GetWindowFcnAddress = 0x5755B0;
	unsigned int GetGadgetFcnAddress = 0x572840;
	__asm {
		PUSH EAX
		PUSH 0
		PUSH 0x610E28
		PUSH 0x6068A0
		PUSH 0
		PUSH 0x610E20
		PUSH 0x60E518
		CALL GetWindowFcnAddress
		MOV  InGameDesktopAddress, EAX
		PUSH ECX
		MOV  ECX, InGameDesktopAddress
		PUSH 0
		PUSH 0x612FE0
		CALL GetGadgetFcnAddress
		MOV  BuildMenuAddress, EAX
		POP  ECX
		POP  EAX
	}

	BuildMenu* buildMenu = (BuildMenu*) BuildMenuAddress;
	BuildButtonAddress = buildMenu->children[pos - 1];

	unsigned int SelectBuildingFcnAddress = 0x4AF800;
	__asm {
		PUSH ECX
		PUSH 1
		MOV  ECX, BuildButtonAddress
		CALL SelectBuildingFcnAddress
		POP  ECX
	}
}