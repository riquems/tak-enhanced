#pragma once
#include "common.h"

#include "Gadget.h"



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


