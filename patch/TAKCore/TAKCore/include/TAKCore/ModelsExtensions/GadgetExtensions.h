#pragma once
#include "TAKCore/common.h"
#include "TAKCore/Models/UI/Window.h"

namespace GadgetExtensions
{
    extern uint32_t vTableFcnAddresses[];

    bool isListBox(Window* gadget, uint32_t baseAddress);
};
