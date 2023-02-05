#pragma once

#include "../../common.h"

class ConsoleOptions;
class DevelopmentOptions;
class GameSetupOptions;
class InterfaceOptions;
class MusicOptions;
class SoundOptions;
class VisualOptions;

class GameOptions
{
public:                                       // offset
    ConsoleOptions* consoleOptions;           // 0x00
    DevelopmentOptions* developmentOptions;   // 0x04
    GameSetupOptions* gameSetupOptions;       // 0x08
    InterfaceOptions* interfaceOptions;       // 0x0C
    MusicOptions* musicOptions;               // 0x10
    SoundOptions* soundOptions;               // 0x14
    VisualOptions* visualOptions;             // 0x18
};
