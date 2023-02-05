#pragma once
#include "Common.hpp"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Functions/FunctionsSignatures.h"

enum class TextureDisplayMode {
    ORIGINAL_SIZE,
    INCREASED_SIZE
};

class RendererDevice
{
    uintptr_t _baseAddress;
 
public:
    RendererDevice(uintptr_t baseAddress);

    TextureDisplayMode getTextureDisplayMode();
};
