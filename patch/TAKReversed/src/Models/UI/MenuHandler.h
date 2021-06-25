#pragma once
#include "../../common.h"

class Gadget;

class MenuHandler
{
public:
	char padding[8];
	uint32_t width;
	uint32_t height;
	Gadget* focusedGadget;
	Gadget* pressedGadget;
	Gadget* mouseHoveredGadget;
};


