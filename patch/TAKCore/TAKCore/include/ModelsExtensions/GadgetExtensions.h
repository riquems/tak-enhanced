#pragma once
#include "../common.h"
#include "../Models/UI/Gadget.h"

namespace GadgetExtensions
{
    uint32_t vTableFcnAddresses[] = { 0x08bc80 };

    bool isListBox(Gadget* gadget, uint32_t baseAddress)
    {
        return *(gadget->vTable) == (vTableFcnAddresses[0] + baseAddress);
    }
};