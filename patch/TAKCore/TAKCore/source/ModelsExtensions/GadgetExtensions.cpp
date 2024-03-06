#include "TAKCore/ModelsExtensions/GadgetExtensions.h"

namespace GadgetExtensions
{
    uint32_t vTableFcnAddresses[] = { 0x08bc80 };

    bool isListBox(Window* window, uint32_t baseAddress)
    {
        return *(window->vTable) == (vTableFcnAddresses[0] + baseAddress);
    }
};