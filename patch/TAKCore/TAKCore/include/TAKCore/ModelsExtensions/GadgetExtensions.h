#pragma once
#include "TAKCore/common.h"
#include "TAKCore/Models/UI/Gadget.h"

namespace GadgetExtensions
{
    extern uint32_t vTableFcnAddresses[];

    bool isListBox(Gadget* gadget, uint32_t baseAddress);
};
