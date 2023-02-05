#pragma once
#include "../../common.h"

#include "WindowHandler.h"
#include "ImageHandler.h"
#include "TextHandler.h"
#include "FontHandler.h"
#include "InputHandler.h"
#include "BrushHandler.h"
#include "CursorHandler.h"
#include "SoundHandler.h"
#include "GraphicsHandler.h"

class GameInterfaceHandler
{
public:
    WindowHandler* windowHandler;
    ImageHandler* imageHandler;
    TextHandler* textHandler;
    FontHandler* fontHandler;
    InputHandler* inputHandler;
    BrushHandler* brushHandler;
    CursorHandler* cursorHandler;
    SoundHandler* soundHandler;
    GraphicsHandler* graphicsHandler;
};



