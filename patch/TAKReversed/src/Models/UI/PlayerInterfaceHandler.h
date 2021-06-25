#pragma once
#include "../../common.h"

#include "MenuHandler.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "FontHandler.h"
#include "InputHandler.h"
#include "BrushHandler.h"
#include "CursorHandler.h"
#include "SoundHandler.h"
#include "GraphicsHandler.h"

class PlayerInterfaceHandler
{
public:
	MenuHandler* menuHandler;
	ImageHandler* imageHandler;
	TextHandler* textHandler;
	FontHandler* fontHandler;
	InputHandler* inputHandler;
	BrushHandler* brushHandler;
	CursorHandler* cursorHandler;
	SoundHandler* soundHandler;
	GraphicsHandler* graphicsHandler;
};



